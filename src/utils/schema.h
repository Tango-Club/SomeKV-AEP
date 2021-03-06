#pragma once

#include <cstdint>
#include <cstring>
#include <string>

namespace Schema {

struct Row {
    int64_t id;
    char user_id[128];
    char name[128];
    int64_t salary;

    std::string to_string() {
        std::string str;

        str += "[";

        str += "id: " + std::to_string(id);
        str += ", ";
        str += "user_id: " + std::string(user_id);
        str += ", ";
        str += "name: " + std::string(name);
        str += ", ";
        str += "salary: " + std::to_string(salary);

        str += "]";

        return str;
    }
};

enum Column { Id = 0, Userid = 1, Name = 2, Salary = 3 };

constexpr int ROW_LENGTH = sizeof(Row);
constexpr int ID_LENGTH = sizeof(Row::id);
constexpr int USERID_LENGTH = sizeof(Row::user_id);
constexpr int NAME_LENGTH = sizeof(Row::name);
constexpr int SALARY_LENGTH = sizeof(Row::salary);

} // namespace Schema
