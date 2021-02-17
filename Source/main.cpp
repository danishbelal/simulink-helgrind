// A minimal example to test Simulink Code with Helgrind.

extern "C"
{
#include "Demo.h"
}

#include <chrono>
#include <future>
#include <iostream>
#include <thread>

template <typename F>
bool is_ready(const std::shared_future<F>& f)
{
    return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

int main()
{
    std::cout << "Running Simulink Model without Synchronization" << std::endl;
    using namespace std::chrono_literals;

    constexpr auto GainNormalId { 0 };
    constexpr auto GainSlowId { 1 };

    Demo_initialize();

    std::promise<void> KillSwitch;
    std::shared_future<void> KillSignal { KillSwitch.get_future() };

    std::thread NormalGainTask([KillSignal] {
        while (true)
        {
            Demo_step(GainNormalId);

            std::this_thread::sleep_for(1ms);
            if (is_ready(KillSignal))
            {
                return;
            }
        }
    });

    std::thread SlowGainTask([KillSignal] {
        while (true)
        {
            Demo_step(GainSlowId);

            std::this_thread::sleep_for(10ms);
            if (is_ready(KillSignal))
            {
                return;
            }
        }
    });

    // Exit after 1s.
    std::this_thread::sleep_for(1s);
    KillSwitch.set_value();

    std::cout << "Waiting for threads to terminate" << std::endl;
    NormalGainTask.join();
    SlowGainTask.join();

    return 0;
}