#include "Arduino.h"
#include "bora.h"

BORA::BORA(Client& wifi) {
    PubSubClient broker(wifi);
    this->broker = broker;

    this->broker_server = 'baboon.rmq.cloudamqp.com';
    this->broker_port = 1883;
    this->broker_user = 'vzriadoh:vzriadoh';
    this->broker_pass = 'Y98z8eUaIYiRv7VO_L3rgBPYMjGFAEyZ';
}

void BORA::begin(const char* secret_key) {
    this->secret_key = secret_key;

    this->broker.setServer("baboon.rmq.cloudamqp.com", 1883);
    this->broker.setCallback([this](char *topic, byte *payload, unsigned int length) {
        this->handleBrokerMessages(topic, payload, length);
    });

    this->connectBroker();
}

void BORA::handleBrokerMessages(char* topic, byte* payload, unsigned int length) {
    String value;
    for(int i = 0; i < length; i++)  {
       char c = (char)payload[i];
       value += c;
    }

    this->values[(String)topic] = value;
    if (value) {
        this->values[(String)topic] = value;
    }
}

bool BORA::loop() {
    this->connectBroker();

    if (this->has_new_data) {
        this->has_new_data = true;
        this->time_now += this->period;
    }

    return this->broker.loop();
}

const char* BORA::generateTopic(String topic) {
    String secret_key = (String)this->secret_key;
    String separator = "/";
    String generatedTopic = secret_key + separator + topic;

    return generatedTopic.c_str();
}

void BORA::sendData(String variable, String value) {
    const char* topic = this->generateTopic(variable);

    if (millis() >= this->time_now + this->period) {
        this->has_new_data = true;
        this->broker.publish(topic, value.c_str());
    }
}

void BORA::setServer(String server, int port, String user, String pass) {
    this->broker_server = server;
    this->broker_port = port;
    this->broker_user = user;
    this->broker_pass = pass;
}

bool BORA::isConnected() {
    return this->broker.connected();
}

int BORA::clientState() {
    return this->broker.state();
}

void BORA::connectBroker() {
    while (!this->broker.connected()) {
        if (this->broker.connect("BORA", "vzriadoh:vzriadoh", "Y98z8eUaIYiRv7VO_L3rgBPYMjGFAEyZ")) {
            this->broker.subscribe(this->generateTopic("#"));
        } else {
            delay(500);
        }
    }
}

int BORA::digitalRead(int pin, String variable) {
    int value = Arduino_h::digitalRead(pin);
    this->sendData(variable, (String)value);

    return value;
}

int BORA::analogRead(int pin, String variable) {
    int value = Arduino_h::analogRead(pin);
    this->sendData(variable, (String)value);

    return value;
}

void BORA::analogWrite(char pin, int value, String variable) {
    this->sendData(variable, (String)value);
    Arduino_h::digitalWrite(pin, value);
}

void BORA::digitalWrite(char pin, int value, String variable) {
    this->sendData(variable, (String)value);
    Arduino_h::digitalWrite(pin, value);
}

String BORA::virtualWrite(String variable, String value) {
    this->sendData(variable, value);
    return value;
}

String BORA::virtualRead(char* variable) {
    return this->values[(String)this->generateTopic(variable)].as<String>();
}