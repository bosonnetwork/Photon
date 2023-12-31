/*
 * Copyright (c) 2023 trinity-tech.io
 * Copyright (c) 2023 -  ~   bosonnetwork.io
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <iostream>

#include "command.h"

class StatCommand : public Command {
public:
    StatCommand() : Command("stat", "Display traffic statistics of current Boson node.") {};

protected:
    void execute() override {
        auto id = node->getId();

        std::cout << "---- Total data traffic ---- " << std::endl;
        std::cout << "Received: " << node->receivedBytesTotal() << " [Bytes]" << std::endl;
        std::cout << "Sent    : " << node->sentBytesTotal() << " [Bytes]" << std::endl;
         std::cout << std::endl;
        std::cout << "---- Average data traffic per second ---- " << std::endl;
        std::cout << "Received: " << node->receivedBytesPerSecond() << " [Bytes/sec]" << std::endl;
        std::cout << "Sent    : " << node->sentBytesPerSecond() << " [Bytes/sec]" << std::endl;
         std::cout << std::endl;
        std::cout << "---- Total messages ---- " << std::endl;
        std::cout << "Received: " << node->receivedMessagesTotal() << std::endl;
        std::cout << "Sent    : " << node->sentMessagesTotal() << std::endl;
        std::cout << "Timeout : " << node->timeoutMessagesTotal() << std::endl;
        std::cout << std::endl;
    }
};
