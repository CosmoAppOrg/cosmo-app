#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <regex>
#include <filesystem>
#include <algorithm>
#include <numeric>
#include <array>

// CLI11
#ifdef CLI11_FOUND
#include <CLI/CLI.hpp>
#endif

// nlohmann/json
#ifdef NLOHMANN_JSON_FOUND
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#endif

// Asio
#ifdef ASIO_FOUND
#include <asio.hpp>
#endif

// cpp-httplib
#ifdef HTTPPLIB_FOUND
#include <httplib.h>
#endif

// spdlog
#ifdef SPDLOG_FOUND
#include <spdlog/spdlog.h>
#endif

// ada-url
#ifdef ADA_FOUND
#include <ada/url.h>
#endif

// stduuid
#ifdef STDUUID_FOUND
#include <stduuid/uuid.h>
#endif

// reproc
#ifdef REPROC_FOUND
#include <reproc++/run.hpp>
#endif

// cpptrace
#ifdef CPPTRACE_FOUND
#include <cpptrace/cpptrace.hpp>
#endif

// date
#ifdef DATE_FOUND
#include <date/date.h>
#endif

// CSV Parser (Vince's)
// We assume a single header csv.h is available if the csv package is found.
#ifdef CSV_FOUND
#include <csv.h>
#endif

// Our own headers
#include "math_utils.h"
#include "embedded_resource.h"
#include "logger.h"

void demo_cli11(int argc, char* argv[]) {
#ifdef CLI11_FOUND
    CLI::App app{"Cosmo App Demo"};
    std::string host = "localhost";
    int port = 80;

    app.add_option("--host", host, "Host name")->default_str("localhost");
    app.add_option("--port", port, "Port number")->default_val(80);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        exit(app.exit(e));
    }

    std::cout << "[CLI11] Host: " << host << ", Port: " << port << std::endl;
#else
    (void)argc; (void)argv;
    std::cout << "[CLI11] Not found (skipped)" << std::endl;
#endif
}

void demo_json() {
#ifdef NLOHMANN_JSON_FOUND
    // Parse the embedded resource
    auto embedded = get_embedded_resource();
    try {
        json j = json::parse(embedded.begin(), embedded.end());
        std::cout << "[JSON] Parsed embedded JSON: " << j.dump(2) << std::endl;
    } catch (const json::parse_error& e) {
        std::cerr << "[JSON] Parse error: " << e.what() << std::endl;
    }
#else
    std::cout << "[JSON] Not found (skipped)" << std::endl;
#endif
}

void demo_asio() {
#ifdef ASIO_FOUND
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::milliseconds(200));
    t.wait();
    std::cout << "[Asio] 200ms timer expired" << std::endl;
#else
    std::cout << "[Asio] Not found (skipped)" << std::endl;
#endif
}

void demo_httplib() {
#ifdef HTTPPLIB_FOUND
    httplib::Client cli("http://example.com");
    auto res = cli.Get("/");
    if (res) {
        std::cout << "[HTTP] Status: " << res->status << std::endl;
        if (res->body.size() > 50) {
            std::cout << "[HTTP] Body (first 50 chars): " << res->body.substr(0, 50) << "..." << std::endl;
        } else {
            std::cout << "[HTTP] Body: " << res->body << std::endl;
        }
    } else {
        std::cerr << "[HTTP] Error: " << httplib::to_string(res.error()) << std::endl;
    }
#else
    std::cout << "[HTTP] Not found (skipped)" << std::endl;
#endif
}

void demo_filesystem() {
    try {
        std::cout << "[Filesystem] Current path: " << std::filesystem::current_path() << std::endl;
        std::cout << "[Filesystem] Contents:" << std::endl;
        for (const auto& entry : std::filesystem::directory_iterator(".")) {
            std::cout << "  - " << entry.path().filename() << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "[Filesystem] Error: " << e.what() << std::endl;
    }
}

void demo_regex() {
    std::string text = "Server 192.168.1.100 port 8080 has 42 connections.";
    std::smatch matches;
    std::regex ip_regex(R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}))");
    std::regex num_regex(R"(\b(\d+)\b)");

    std::cout << "[Regex] Text: \"" << text << "\"" << std::endl;

    if (std::regex_search(text, matches, ip_regex)) {
        std::cout << "[Regex] IP address found: " << matches[1] << std::endl;
    }

    std::cout << "[Regex] Numbers found: ";
    auto words_begin = std::sregex_iterator(text.begin(), text.end(), num_regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::cout << match.str() << " ";
    }
    std::cout << std::endl;
#else
    std::cout << "[Regex] Not available (requires <regex>, which is standard)" << std::endl;
#endif
}

void demo_thread_future() {
    auto future = std::async(std::launch::async, [] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return 42;
    });

    std::cout << "[Thread/Future] Waiting for async task..." << std::endl;
    int result = future.get();
    std::cout << "[Thread/Future] Async task returned: " << result << std::endl;
}

void demo_cpp17_algorithms() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // transform: multiply each by 2
    std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x * 2; });
    std::cout << "[C++17] After transform (x2): ";
    for (int n : v) std::cout << n << " ";
    std::cout << std::endl;

    // copy_if: copy even numbers
    std::vector<int> evens;
    std::copy_if(v.begin(), v.end(), std::back_inserter(evens), [](int x) { return x % 2 == 0; });
    std::cout << "[C++17] Even numbers: ";
    for (int n : evens) std::cout << n << " ";
    std::cout << std::endl;

    // reduce: sum of all elements
    int sum = std::reduce(v.begin(), v.end(), 0, std::plus<>());
    std::cout << "[C++17] Sum of elements: " << sum << std::endl;
}

void demo_embedded_resource() {
    auto embedded = get_embedded_resource();
    std::cout << "[Embedded Resource] Size: " << embedded.size() << " bytes" << std::endl;
    std::cout << "[Embedded Resource] Content: " << embedded << std::endl;
}

void demo_spdlog() {
#ifdef SPDLOG_FOUND
    auto logger = setup_logger();
    logger->info("Hello from spdlog!");
    logger->warn("This is a warning message");
    logger->error("This is an error message");
    // Flush to ensure logs are written
    logger->flush();
#else
    std::cout << "[spdlog] Not found (skipped)" << std::endl;
#endif
}

void demo_ada_url() {
#ifdef ADA_FOUND
    ada::url url("https://example.com:8080/path?name=value#section");
    std::cout << "[ADA URL] Original: " << url.serial() << std::endl;

    // Mutate: set a new path
    url.set_path("/newpath");
    url.set_query("newquery=test");
    std::cout << "[ADA URL] Modified: " << url.serial() << std::endl;
#else
    std::cout << "[ADA URL] Not found (skipped)" << std::endl;
#endif
}

void demo_stduuid() {
#ifdef STDUUID_FOUND
    // Generate a random UUID (version 4)
    stduuid::uuid u1 = stduuid::uuid::random();
    std::cout << "[STDUUID] Random UUID: " << u1 << std::endl;

    // Generate a name-based UUID (version 5) using a namespace and a name
    stduuid::uuid u2 = stduuid::uuid::name_based(stduuid::uuid::ns::dns(), "example.com");
    std::cout << "[STDUUID] Name-based UUID: " << u2 << std::endl;
#else
    std::cout << "[STDUUID] Not found (skipped)" << std::endl;
#endif
}

void demo_reproc() {
#ifdef REPROC_FOUND
    try {
        // Run `cmake --version` and capture the output
        reproc::options opts;
        opts.redirect.parent = true; // Use parent's stdout/stderr
        auto result = reproc::run({ "cmake", "--version" }, opts);
        if (result.exit_status == 0) {
            std::cout << "[REPROC] cmake --version succeeded" << std::endl;
        } else {
            std::cerr << "[REPROC] cmake --version failed with exit code: " << result.exit_status << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[REPROC] Exception: " << e.what() << std::endl;
    }
#else
    std::cout << "[REPROC] Not found (skipped)" << std::endl;
#endif
}

void demo_cpptrace() {
#ifdef CPPTRACE_FOUND
    cpptrace::snapshot trace = cpptrace::snapshot::current();
    std::cout << "[CPPTRACE] Stack trace (" << trace.frames.size() << " frames):" << std::endl;
    for (size_t i = 0; i < trace.frames.size(); ++i) {
        const auto& frame = trace.frames[i];
        std::cout << "  #" << i << " " << frame.object << " at " << frame.load_address << " (" << frame.filename << ":" << frame.line << ")" << std::endl;
    }
#else
    std::cout << "[CPPTRACE] Not found (skipped)" << std::endl;
#endif
}

void demo_date() {
#ifdef DATE_FOUND
    using namespace date;
    using namespace std::chrono;

    // Today's date
    auto today = floor<days>(system_clock::now());
    year_month_day ymd = today;

    std::cout << "[DATE] Today: " << ymd << std::endl;

    // Add 10 days
    auto ten_days_later = today + days{10};
    year_month_day ymd_later = ten_days_later;
    std::cout << "[DATE] Today + 10 days: " << ymd_later << std::endl;

    // Weekday of today
    weekday wd = ymd.weekday();
    std::cout << "[DATE] Today's weekday: " << wd << " (iso: " << static_cast<unsigned>(wd) << ")" << std::endl;

    // Difference between two dates
    auto new_year = year_month_day{year{static_cast<int>(ymd.year())}/12/31};
    auto days_diff = (sys_days{new_year} - sys_days{ymd}).count();
    std::cout << "[DATE] Days until New Year's Eve: " << days_diff << std::endl;
#else
    std::cout << "[DATE] Not found (skipped)" << std::endl;
#endif
}

void demo_csv() {
#ifdef CSV_FOUND
    std::string csv_data = R"csv(name,age,score
Alice,30,85.5
Bob,25,92.0
Charlie,35,78.5
)csv";

    try {
        csv::CSVReader reader(csv_data);
        std::cout << "[CSV] Headers: ";
        for (auto& header : reader.get_header()) {
            std::cout << header << " ";
        }
        std::cout << std::endl;

        std::cout << "[CSV] Rows:" << std::endl;
        for (auto& row : reader) {
            std::string name = row["name"];
            int age = row["age"];
            double score = row["score"];
            std::cout << "  - " << name << ", age: " << age << ", score: " << score << std::endl;
        }
    } catch (const csv::Error& e) {
        std::cerr << "[CSV] Error: " << e.what() << std::endl;
    }
#else
    std::cout << "[CSV] Not found (skipped)" << std::endl;
#endif
}

int main(int argc, char* argv[]) {
    std::cout << "=== Cosmo App: C++ Library Demonstration ===" << std::endl;

    demo_cli11(argc, argv);
    demo_json();
    demo_asio();
    demo_httplib();
    demo_filesystem();
    demo_regex();
    demo_thread_future();
    demo_cpp17_algorithms();
    demo_embedded_resource();
    demo_spdlog();
    demo_ada_url();
    demo_stduuid();
    demo_reproc();
    demo_cpptrace();
    demo_date();
    demo_csv();

    std::cout << "=== End of Demonstrations ===" << std::endl;
    return 0;
}