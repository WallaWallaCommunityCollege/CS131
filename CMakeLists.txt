cmake_minimum_required(VERSION 3.6)
project(cs131)
set(CMAKE_CXX_STANDARD 11)
# week1
add_executable(ch1p20_peas_michael_cummings week1/ch1p20_peas_michael_cummings.cpp)
add_executable(ch1p35_5plus_more_michael_cummings week1/ch1p35_5plus_more_michael_cummings.cpp)
# week2
add_executable(ch2_6pay_michael_cummings week2/ch2_6pay_michael_cummings.cpp)
add_executable(ch2_in_class_michael_cummings week2/ch2_in_class_michael_cummings.cpp)
#add_executable(ch2n3work week2/ch2n3work.cpp)
# week3
add_executable(ch3_4blackjack_michael_cummings week3/ch3_4blackjack_michael_cummings.cpp)
add_executable(ch3_guess_michael_cummings week3/ch3guess_michael_cummings.cpp)
#add_executable(03-04 week3/TextSourceCh3/03-04.cpp)
# week4
add_executable(04-01 week4/Chapter04/04-01.cpp)
add_executable(ch4_7time_machine_michael_cummings week4/ch4_7time_machine_michael_cummings.cpp)
add_executable(junk week4/test.cpp)
# week5
add_executable(ch5_4coin_michael_cummings week5/ch5_4coin_michael_cummings.cpp)
add_executable(ReadWriteFile week5/ReadWriteFile.cpp)
configure_file(${CMAKE_SOURCE_DIR}/week5/infile.dat ${CMAKE_CURRENT_BINARY_DIR}/infile.dat COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/week5/scores.dat ${CMAKE_CURRENT_BINARY_DIR}/scores.dat COPYONLY)
add_executable(ch6_2scores_michael_cummings week5/ch6_2scores_michael_cummings.cpp)
