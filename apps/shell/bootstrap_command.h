/*
 * Copyright (c) 2022 - 2023 trinity-tech.io
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
#include <string>

#include "command.h"

class BootstrapCommand : public Command {
public:
    BootstrapCommand() : Command("bootstrap", "Bootstrap from the node.") {};

protected:
    void setupOptions() override {
        add_option("ID", id, "The node id.");
        add_option("ADDRESS", address, "The node address.");
        add_option("PORT", port, "The node port.");
        require_option(3, 3);
    };

    void execute() override {
        if (port <= 0) {
            std::cout << "----------------------------------------------" << std::endl
                      << "Invalid port: " << port << std::endl
                      << "----------------------------------------------" << std::endl;
            return;
        }

        auto nodeid = Id(id);
        auto ni = NodeInfo(nodeid, address, port);
        node->bootstrap(ni);
    };

private:
    std::string id {};
    std::string address {};
    int port = 0;

};
