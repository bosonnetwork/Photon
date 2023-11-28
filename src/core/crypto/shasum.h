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

#include <vector>
#include "boson/blob.h"

namespace boson {

class SHA256 {
public:
    static const uint32_t BYTES { 32 };

    SHA256() noexcept {
        reset();
    }

    void reset();

    void update(const Blob& part);

    void digest(Blob& hash);

    std::vector<uint8_t> digest() {
        std::vector<uint8_t> hash(BYTES);
        Blob _hash{hash};
        digest(_hash);
        return hash;
    }

    static void digest(Blob& hash, const Blob& data);

    static std::vector<uint8_t> digest(const Blob& data) {
        std::vector<uint8_t> hash(BYTES);
        Blob _hash{hash};
        digest(_hash, data);
        return hash;
    }

private:
    struct DigestState { uint8_t __opaque__[128]; };
    DigestState state;
};

} // namespace boson
