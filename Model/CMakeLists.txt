# I really need to script this task...

set(ModelName Demo)
set(ModelPath "${CMAKE_CURRENT_SOURCE_DIR}/ec-multithreading/${ModelName}_ert_rtw")

set(ModelSources "${ModelPath}/${ModelName}.c"
                         "${ModelPath}/${ModelName}.h"
                         "${ModelPath}/${ModelName}_types.h"
                         "${ModelPath}/${ModelName}_private.h")

# set(ExtraPath "${CMAKE_CURRENT_SOURCE_DIR}/R2019b")
# set(ExtraSources "${ExtraPath}/rtw/c/src/rtw_capi.h"
#                  "${ExtraPath}/rtw/c/src/rtw_modelmap_logging.h"
#                  "${ExtraPath}/rtw/c/src/rtw_modelmap.h"
#                  "${ExtraPath}/simulink/include/sysran_types.h")

# Submodel Sources
set(SubmodelPath "${CMAKE_CURRENT_SOURCE_DIR}/ec-multithreading/slprj/ert")
set(SubmodelSources "${SubmodelPath}/Gain/Gain.c"
                    "${SubmodelPath}/Gain/Gain.h"
                    "${SubmodelPath}/Gain/Gain_private.h"
                    "${SubmodelPath}/Gain/Gain_types.h"
                    "${SubmodelPath}/SlowGain/SlowGain.c"
                    "${SubmodelPath}/SlowGain/SlowGain.h"
                    "${SubmodelPath}/SlowGain/SlowGain_private.h"
                    "${SubmodelPath}/SlowGain/SlowGain_types.h")

# Shared Sources
set(SharedPath "${CMAKE_CURRENT_SOURCE_DIR}/ec-multithreading/slprj/ert/_sharedutils")
set(SharedSouces "${SharedPath}/rtwtypes.h")

set(AllIncludes "${ModelPath}"
                "${SubmodelPath}/Gain"
                "${SubmodelPath}/SlowGain"
                "${SubmodelPath}/_sharedutils"
                "${SharedPath}")

set(AllSources "${ModelSources}"
               "${SubmodelSources}"
               "${SharedSources}")

add_library(DemoModel "${AllSources}")
target_include_directories(DemoModel PUBLIC "${AllIncludes}")