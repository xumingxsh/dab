#pragma once

#include <string>
#include <functional>
#include <map>
#include "context/dab_context.h"

/**
 * @class TopicHandler
 * @brief Handles MQTT topics and their associated callback functions.
 * 
 * This class provides functionality to initialize, destroy, and manage topic handlers.
 * It also processes incoming MQTT messages and routes them to the appropriate handlers.
 */
class TopicHandler {
public:
    /**
     * @brief Initializes the TopicHandler with a maximum number of threads.
     * @param maxThreads The maximum number of threads allowed for processing topics.
     */
    static void init(int maxThreads);

    /**
     * @brief Destroys the TopicHandler and releases any resources.
     */
    static void destroy();

    /**
     * @brief Registers topic handlers.
     * @param handles A map of topic names to their corresponding handler functions.
     */
    static void registerHandler(const std::map<std::string, std::function<void(DABContext&)>>& handles);

public:
    /**
     * @brief Callback function for handling incoming MQTT messages.
     * @param topic The topic of the incoming message.
     * @param body The body (payload) of the incoming message.
     * @param response_topic The topic to which the response should be sent.
     * @param correlation_data Correlation data for the message.
     */
    static void onTopic(const char* topic, const char* body, const char* response_topic, const char* correlation_data);
public:
    TopicHandler() = delete;
};