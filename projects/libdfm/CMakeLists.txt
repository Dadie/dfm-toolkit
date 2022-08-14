cmake_minimum_required(VERSION 3.8)

# Project Information
project (libdfm VERSION 0.4.0 LANGUAGES CXX)

# Source
set (SOURCES
    "src/dfm/lexer/lex.cpp"
    "src/dfm/lexer/token_matcher.cpp"
    "src/dfm/lexer/token.cpp"
    "src/dfm/lexer/weed.cpp"

    "src/dfm/pt/weed.cpp"
    "src/dfm/pt/node.cpp"

    "src/dfm/pt/parse/value_array_item.cpp"
    "src/dfm/pt/parse/value_array_item_param.cpp"
    "src/dfm/pt/parse/value_array_item_param_name.cpp"
    "src/dfm/pt/parse/value_array_items.cpp"
    "src/dfm/pt/parse/any_chars.cpp"
    "src/dfm/pt/parse/dfm.cpp"
    "src/dfm/pt/parse/hex_code_string.cpp"
    "src/dfm/pt/parse/nl.cpp"
    "src/dfm/pt/parse/hws.cpp"
    "src/dfm/pt/parse/ws.cpp"
    "src/dfm/pt/parse/obj.cpp"
    "src/dfm/pt/parse/obj_name.cpp"
    "src/dfm/pt/parse/obj_param.cpp"
    "src/dfm/pt/parse/obj_param_name.cpp"
    "src/dfm/pt/parse/obj_params.cpp"
    "src/dfm/pt/parse/obj_type.cpp"
    "src/dfm/pt/parse/value_set_value.cpp"
    "src/dfm/pt/parse/value_set_values.cpp"
    "src/dfm/pt/parse/token.cpp"
    "src/dfm/pt/parse/value.cpp"
    "src/dfm/pt/parse/value_array.cpp"
    "src/dfm/pt/parse/value_binary.cpp"
    "src/dfm/pt/parse/value_bit.cpp"
    "src/dfm/pt/parse/value_constant.cpp"
    "src/dfm/pt/parse/value_float.cpp"
    "src/dfm/pt/parse/value_integer.cpp"
    "src/dfm/pt/parse/value_set.cpp"
    "src/dfm/pt/parse/value_string.cpp"
    "src/dfm/pt/parse/value_string_element.cpp"
    "src/dfm/pt/parse/value_string_element_string.cpp"
    "src/dfm/pt/parse/value_string_element_char.cpp"
    "src/dfm/pt/parse/value_inline_object.cpp"
    "src/dfm/pt/parse/value_datetime.cpp"
    "src/dfm/pt/parse/delphi_identifier.cpp"
    "src/dfm/pt/parse/delphi_name.cpp"
    "src/dfm/pt/parse/helper.cpp"

    "src/dfm/ast/load.cpp"
    "src/dfm/ast/node.cpp"
    "src/dfm/ast/node_dfm.cpp"
    "src/dfm/ast/node_object.cpp"
    "src/dfm/ast/node_parameter.cpp"
    "src/dfm/ast/node_value_integer.cpp"
    "src/dfm/ast/node_value_float.cpp"
    "src/dfm/ast/node_value_constant.cpp"
    "src/dfm/ast/node_value_string.cpp"
    "src/dfm/ast/node_value_binary.cpp"
    "src/dfm/ast/node_value_bit.cpp"
    "src/dfm/ast/node_value_set.cpp"
    "src/dfm/ast/node_value_array.cpp"
    "src/dfm/ast/node_value_array_item.cpp"
    "src/dfm/ast/node_value_inline_object.cpp"
    "src/dfm/ast/node_value_datetime.cpp"

    "src/dfm/ast/parse/dfm.cpp"
    "src/dfm/ast/parse/obj.cpp"
    "src/dfm/ast/parse/parameter.cpp"
    "src/dfm/ast/parse/values.cpp"
    "src/dfm/ast/parse/helper.cpp"

    "src/dfm/utils/debug.cpp"
    "src/dfm/utils/ci_compare.cpp"
    "src/dfm/utils/iconv.cpp"
    "src/dfm/utils/bits.cpp"
    "src/dfm/utils/io.cpp"
    "src/dfm/utils/image/bmp32.cpp"
    "src/dfm/utils/form/envelope.cpp"
    "src/dfm/utils/form/find.cpp"
    "src/dfm/utils/form/identifier.cpp"

)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

# Set compiler options
target_compile_options(${PROJECT_NAME} PUBLIC "-Wall")
target_compile_options(${PROJECT_NAME} PUBLIC "-Wpedantic")
target_compile_options(${PROJECT_NAME} PUBLIC "-Wextra")
target_compile_options(${PROJECT_NAME} PUBLIC "-pthread")
target_compile_options(${PROJECT_NAME} PUBLIC "-fPIC")
target_compile_options(${PROJECT_NAME} PUBLIC "-O3")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

enable_testing()
add_subdirectory(test)
