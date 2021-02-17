add_executable(SimulinkDemo "main.cpp")
target_link_libraries(SimulinkDemo PRIVATE DemoModel Threads::Threads)
