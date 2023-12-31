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

#include "log_tests.h"

#include <stdio.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_DIRENT_H
#include <dirent.h>
#endif
#ifdef HAVE_IO_H
#include <io.h>
#endif
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// std
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

#include "utils.h"
#include "utils/log.h"

#include <boson.h>
using namespace boson;

namespace test {
CPPUNIT_TEST_SUITE_REGISTRATION(LoggerTester);

void
LoggerTester::setUp() {

}

void LoggerTester::testNormal() {
    puts("\n*--- test normal ---*");
    auto log = Logger::get("testNormal");
    auto name = log->getName();
    CPPUNIT_ASSERT(name == "testNormal");
    CPPUNIT_ASSERT(log->isInfoEnabled());
    CPPUNIT_ASSERT(log->isEnabled(Level::Info));

    log->setLevel(Level::Critical);
    CPPUNIT_ASSERT(log->isCriticalEnabled());
    log->setLevel(Level::Error);
    CPPUNIT_ASSERT(log->isErrorEnabled());
    log->setLevel(Level::Warn);
    CPPUNIT_ASSERT(log->isWarnEnabled());
    log->setLevel(Level::Info);
    CPPUNIT_ASSERT(log->isInfoEnabled());
    log->setLevel(Level::Debug);
    CPPUNIT_ASSERT(log->isDebugEnabled());
    log->setLevel(Level::Trace);
    CPPUNIT_ASSERT(log->isTraceEnabled());
    CPPUNIT_ASSERT(!log->isInfoEnabled());

    log->setPattern("[%n] %^[%l] %v%$");

    log->setLevel(Level::Critical);
    CPPUNIT_ASSERT(log->isCriticalEnabled());
    CPPUNIT_ASSERT(!log->isInfoEnabled());
    log->critical("Level critical: test {}", "Critical");
    log->error("Level critical: test {}", "Error");
    log->warn("Level critical: test {}", "Warn");
    log->info("Level critical: test {}", "Info");
    log->debug("Level critical: test {}", "Debug");
    log->trace("Level critical: test {}", "Trace");

    puts("");
    log->setLevel(Level::Error);
    CPPUNIT_ASSERT(log->isErrorEnabled());
    log->critical("Level error: test {}", "Critical");
    log->error("Level error: test {}", "Error");
    log->warn("Level error: test {}", "Warn");
    log->info("Level error: test {}", "Info");
    log->debug("Level error: test {}", "Debug");
    log->trace("Level error: test {}", "Trace");

    puts("");
    log->setLevel(Level::Warn);
    CPPUNIT_ASSERT(log->isWarnEnabled());
    log->critical("Level warn: test {}", "Critical");
    log->error("Level warn: test {}", "Error");
    log->warn("Level warn: test {}", "Warn");
    log->info("Level warn: test {}", "Info");
    log->debug("Level warn: test {}", "Debug");
    log->trace("Level warn: test {}", "Trace");

    puts("");
    log->setLevel(Level::Info);
    CPPUNIT_ASSERT(log->isInfoEnabled());
    log->critical("Level info: test {}", "Critical");
    log->error("Level info: test {}", "Error");
    log->warn("Level info: test {}", "Warn");
    log->info("Level info: test {}", "Info");
    log->debug("Level info: test {}", "Debug");
    log->trace("Level info: test {}", "Trace");

    puts("");
    log->setLevel(Level::Debug);
    CPPUNIT_ASSERT(log->isDebugEnabled());
    log->critical("Level debug: test {}", "Critical");
    log->error("Level debug: test {}", "Error");
    log->warn("Level debug: test {}", "Warn");
    log->info("Level debug: test {}", "Info");
    log->debug("Level debug: test {}", "Debug");
    log->trace("Level debug: test {}", "Trace");

    puts("");
    log->setLevel(Level::Trace);
    CPPUNIT_ASSERT(log->isTraceEnabled());
    CPPUNIT_ASSERT(!log->isInfoEnabled());
    log->critical("Level trace: test {}", "Critical");
    log->error("Level trace: test {}", "Error");
    log->warn("Level trace: test {}", "Warn");
    log->info("Level trace: test {}", "Info");
    log->debug("Level trace: test {}", "Debug");
    log->trace("Level trace: test {}", "Trace");

}

void LoggerTester::testMacro() {
    puts("\n*--- test macro ---*");
    auto log = Logger::get("testMacro");
    auto name = log->getName();
    CPPUNIT_ASSERT(name == "testMacro");
    log->setLevel(Level::Info);

    log->setPattern("[%Y-%m-%d %T] [%@] [%!] [%n] %^[%l] %v%$");
    BOSON_LOGGER_CRITICAL(log, "Level info: critical message.. {} ,{}", 1, 3.23);
    BOSON_LOGGER_ERROR(log, "Level info: error message.. {} ,{}", 1, 3.23);
    BOSON_LOGGER_WARN(log, "Level info: warn message.. {} ,{}", 1, 3.23);
    BOSON_LOGGER_INFO(log, "Level info: info message.. {} ,{}", 1, 3.23);
    BOSON_LOGGER_DEBUG(log, "Level info: debug message.. {} ,{}", 1, 3.23);
    BOSON_LOGGER_TRACE(log, "Level info: trace message.. {} ,{}", 1, 3.23);

    puts("");
    log->setLevel(Level::Trace);
    CPPUNIT_ASSERT(log->isTraceEnabled());
    BOSON_LOGGER_CRITICAL(log, "Level trace: critical message.. {} ,{}", 1, 3.23);
    BOSON_LOGGER_ERROR(log, "Level trace: error message.. {} ,{}", 1, 3.23);
    BOSON_LOGGER_WARN(log, "Level trace: warn message.. {} ,{}", 1, 3.23);
    BOSON_LOGGER_INFO(log, "Level trace: info message.. {} ,{}", 1, 3.23);
    BOSON_LOGGER_DEBUG(log, "Level trace: debug message.. {} ,{}", 1, 3.23);
    BOSON_LOGGER_TRACE(log, "Level trace: trace message.. {} ,{}", 1, 3.23);
}

void LoggerTester::testConf() {
    puts("\n*--- test conf ---*");
    std::string path = ".";
    std::string file = "log_test.conf";
    auto fullpath = path + Utils::PATH_SEP + file;
    bool exist = false;
    if (!Utils::isFileExists(fullpath)) {
        file = "tests/apitests/log_test.conf";
        fullpath = path + Utils::PATH_SEP + file;
        exist = Utils::isFileExists(fullpath);
    }
    Utils::removeStorage("./log");

    fullpath = path + Utils::PATH_SEP + file;
    Logger::initialize(fullpath);
    auto log = Logger::get("root");
    auto name = log->getName();
    log->critical("critical test.");
    log->error("error test.");
    log->warn("warn test.");
    log->info("info test.");
    log->debug("debug test.");
    log->trace("trace test.");

    path = path + Utils::PATH_SEP + "log";
    file = "test.log";
    fullpath = path + Utils::PATH_SEP + file;
    CPPUNIT_ASSERT(Utils::isFileExists(fullpath));
    std::ifstream infile(fullpath);
    CPPUNIT_ASSERT(infile.is_open());
    std::string line = "";
    // CPPUNIT_ASSERT(getline(infile, line));
    // CPPUNIT_ASSERT(line == "[critical] critical test.");
    // CPPUNIT_ASSERT(getline(infile, line));
    // CPPUNIT_ASSERT(line == "[error] error test.");
    // CPPUNIT_ASSERT(getline(infile, line));
    // CPPUNIT_ASSERT(line == "[warning] warn test.");
    // CPPUNIT_ASSERT(getline(infile, line));
    // CPPUNIT_ASSERT(line == "[info] info test.");
    // CPPUNIT_ASSERT(getline(infile, line));
    // CPPUNIT_ASSERT(line == "[debug] debug test.");
    // CPPUNIT_ASSERT(getline(infile, line));
    // CPPUNIT_ASSERT(line == "[trace] trace test.");
    // CPPUNIT_ASSERT(infile.eof());
    infile.close();

    file = "test_err.log";
    fullpath = path + Utils::PATH_SEP + file;
    CPPUNIT_ASSERT(Utils::isFileExists(fullpath));
    std::ifstream infile_err(fullpath.c_str());
    CPPUNIT_ASSERT(infile_err.is_open());
    // CPPUNIT_ASSERT(getline(infile_err, line));
    // CPPUNIT_ASSERT(line == "[critical] critical test.");
    // CPPUNIT_ASSERT(getline(infile_err, line));
    // CPPUNIT_ASSERT(line == "[error] error test.");
    // CPPUNIT_ASSERT(infile.eof());
    infile_err.close();

    puts("");
    log = Logger::get("console");
    name = log->getName();
    log->trace(name + " trace test.");
    log->info(name + " info test.");
}

void
LoggerTester::tearDown() {

}
}  // namespace test
