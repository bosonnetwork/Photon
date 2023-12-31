/*
* Copyright (c) 2022 - 2023 trinity-tech.io
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

#include <sstream>

#include "crypto/hex.h"
#include "message_error.h"
#include "serializers.h"
#include "store_value_request.h"

namespace boson {

void StoreValueRequest::setValue(const Value& value) {
    if (value.isMutable()) {
        this->publicKey = value.getPublicKey();
        this->nonce = value.getNonce();
        this->signature = value.getSignature();
        this->sequenceNumber = value.getSequenceNumber();
        if (value.isEncrypted())
            this->recipient = value.getRecipient();
    }
    this->value = value.getData();
}

Value StoreValueRequest::getValue() const {
    return Value::of(publicKey.has_value() ? publicKey.value().blob(): Blob(), {},
        recipient.has_value() ? recipient.value().blob(): Blob(),
        nonce.has_value() ? nonce.value().blob(): Blob(), sequenceNumber,
        signature.has_value() ? signature.value() : Blob(), value);
}

void StoreValueRequest::serializeInternal(nlohmann::json& root) const {
    nlohmann::json object = nlohmann::json::object();

    object[KEY_REQ_TOKEN] = token;
    if (isMutable()) {
        object[KEY_REQ_PUBLICKEY] = publicKey.value();
        if (isEncrypted())
            object[KEY_REQ_RECIPIENT] = recipient.value();
        object[KEY_REQ_NONCE] = nlohmann::json::binary_t {{nonce.value().cbegin(), nonce.value().cend()}};
        object[KEY_REQ_SIGNATURE] = nlohmann::json::binary_t {signature.value()};
        if (sequenceNumber >= 0)
            object[KEY_REQ_SEQ] = sequenceNumber;
        if (expectedSequenceNumber >= 0)
            object[KEY_REQ_CAS] = expectedSequenceNumber;
    }

    object[KEY_REQ_VALUE] = nlohmann::json::binary_t {value};

    Message::serializeInternal(root);
    root[getKeyString()] = object;
}

void StoreValueRequest::parse(const std::string& fieldName, nlohmann::json& object) {
    if (fieldName != KEY_REQUEST || !object.is_object())
        throw MessageError("Invalid request message");

    for (const auto& [key, object] : object.items()) {
        if (key == KEY_REQ_PUBLICKEY) {
            publicKey = object.get<Id>();
        } else if (key == KEY_REQ_RECIPIENT) {
            recipient = object.get<Id>();
        } else if (key == KEY_REQ_NONCE) {
            nonce = CryptoBox::Nonce(Blob(object.get_binary()));
        } else if (key == KEY_REQ_SIGNATURE) {
           signature = object.get_binary();
        } else if (key == KEY_REQ_SEQ) {
            sequenceNumber = object.get<uint16_t>();
        } else if (key == KEY_REQ_CAS) {
            object.get_to(expectedSequenceNumber);
        } else if (key == KEY_REQ_TOKEN) {
            object.get_to(token);
        } else if (key == KEY_RES_VALUE) {
            value = object.get_binary();
        } else {
            throw MessageError("Unknown field: " + key);
        }
    }
}

void StoreValueRequest::toString(std::stringstream& ss) const {
    ss << ",q:{";

    if (isMutable()) {
        ss << ",k:" << publicKey.value().toString();
        if (isEncrypted())
            ss << ",rec:" << recipient.value().toString();
        ss << ",n:" << Hex::encode(nonce.value().blob());
        if (sequenceNumber >= 0)
            ss << ",seq:" << std::to_string(sequenceNumber);
        ss << ",sig:" << Hex::encode(signature.value());
        if (expectedSequenceNumber >= 0)
            ss << ",cas:" << std::to_string(expectedSequenceNumber);

        ss << ",";
    }

    ss << "tok:" << std::to_string(token)
        << ",v:" << Hex::encode(value)
        << "}";
}

}  // namespace boson
