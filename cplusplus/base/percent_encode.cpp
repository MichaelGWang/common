#include <assert.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

std::string url_encode(const std::string& raw_url) {
    if (raw_url.empty()) {
        return raw_url;
    }

    std::ostringstream escaped;

    escaped.fill('0');
    escaped << std::hex;

    auto non_reserved = [](char ch) -> bool {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
               (ch >= '0' && ch <= '9') || ch == '-' || ch == '_' ||
               ch == '.' || ch == '~';
    };

    for (auto& ch : raw_url) {
        // Keep alphanumeric and other accepted characters intact
        if (non_reserved(ch)) {
            escaped << ch;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << std::uppercase;
        escaped << '%' << std::setw(2)
                << static_cast<int>(static_cast<unsigned char>(ch));
        escaped << std::nouppercase;
    }

    return escaped.str();
}

std::string url_decode(const std::string& url) {
    if (url.empty()) {
        return url;
    }

    std::string raw;

    enum { state_normal, state_convert_1, state_convert_2 };

    int state = state_normal;
    int oct = 0;

    for (auto& ch : url) {
        switch (state) {
            case state_normal:
                if (ch == '%') {
                    state = state_convert_1;
                } else {
                    raw.push_back(ch);
                }
                break;

            case state_convert_1:
                oct = ch >= 'A' && ch <= 'Z'
                          ? (ch - 'A') + 10
                          : ch >= 'a' && ch <= 'b' ? (ch - 'a') + 10 : ch - '0';
                oct *= 16;
                state = state_convert_2;
                break;

            case state_convert_2:
                oct +=
                    ch >= 'A' && ch <= 'Z'
                        ? (ch - 'A') + 10
                        : ch >= 'a' && ch <= 'b' ? (ch - 'a') + 10 : ch - '0';
                raw.push_back(static_cast<char>(oct));
                state = state_normal;
                break;
        }
    }

    return std::move(raw);
}

int main() {
    std::string url = "http://www.example.com?a=1&b=2";
    std::string expect = "http%3A%2F%2Fwww.example.com%3Fa%3D1%26b%3D2";
    std::string escaped = url_encode(url);

    assert(expect == escaped);
    assert(url == url_decode(escaped));

    return 0;
}
