#pragma once

#include <string>
#include <vector>
#include <functional>

/**
 * @class HiMqttClient
 * @brief A simple MQTT client class for handling MQTT communication.
 * 
 * This class provides basic MQTT functionalities such as connecting to a broker,
 * subscribing to topics, publishing messages, and handling incoming messages.
 */
class HiMqttClient {
public:
    /**
     * @brief Starts the MQTT client and connects to the broker.
     * 
     * @param ip The IP address of the MQTT broker.
     * @param port The port of the MQTT broker.
     * @param user The username for authentication (optional, can be nullptr).
     * @param password The password for authentication (optional, can be nullptr).
     * @param clientId The unique client ID for this connection.
     */
    static void start(const char* ip, int port, const char* user, const char* password, const char* clientId);

    /**
     * @brief Stops the MQTT client and disconnects from the broker.
     */
    static void stop();
public:
    /**
     * @brief Subscribes to a list of topics.
     * 
     * @param topics A vector of topic strings to subscribe to.
     */
    static void subscribe(const std::vector<std::string>& topics);

    /**
     * @brief Publishes a message to a specific topic.
     * 
     * @param topic The topic to publish the message to.
     * @param body The message payload.
     * @return True if the message was published successfully, false otherwise.
     */
    static bool publish(const char* topic, const char* body);
public:
    /**
     * @brief Sets a callback function to handle incoming messages.
     * 
     * The callback function will be invoked when a message is received on a subscribed topic.
     * 
     * @param func A function with the following signature:
     *             void(const char* topic, const char* payload, const char* qos, const char* retain)
     *             - topic: The topic of the incoming message.
     *             - payload: The message payload.
     *             - responseTopic: The Response topic name.
     *             - correlation: correlation data.
     */
    static void onTopic(const std::function<void(const char*, const char*, const char*, const char*)>& func);
};