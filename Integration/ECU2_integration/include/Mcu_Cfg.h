/*
 * Mcu_Cfg.h
 *
 *  Created on: May 5, 2018
 *      Author: Ahmed Usama Khalifa
 */

#ifndef INCLUDES_MCU_CFG_H_
#define INCLUDES_MCU_CFG_H_
#include "stdint.h"
typedef uint32_t Mcu_ClockType;


typedef struct McuClockReferencePoint {
    uint32_t McuClockReferencePointFrequency;
}McuClockReferencePoint_t;

typedef struct {
    // This parameter shall represent the Data pre-setting to be initialized
    uint32_t McuRamDefaultValue;

    // This parameter shall represent the MCU RAM section base address
    uint32_t McuRamSectionBaseAddress;

    // This parameter shall represent the MCU RAM Section size
    uint32_t McuRamSectionSize;

} Mcu_RamSectorSettingConfigType;
typedef struct {
    uint32_t AHBClocksEnable;
    uint32_t APB1ClocksEnable;
    uint32_t APB2ClocksEnable;
} Mcu_PerClockConfigType;

/*
[SWS_Mcu_00131]: The structure Mcu_ConfigType is an external data structure
 and shall contain the initialization data for the MCU module. It shall contain:
  MCU dependent properties
  Reset Configuration
  Definition of MCU modes
  Definition of Clock settings
  Definition of RAM sections */
typedef struct {
    //  Enables/Disables clock failure notification. In case this feature is not supported
    //  by HW the setting should be disabled.
    uint8_t   McuClockSrcFailureNotification;

    //  This parameter shall represent the number of Modes available for the
    //  MCU. calculationFormula = Number of configured McuModeSettingConf
    //uint8_t McuNumberOfMcuModes; /* Not supported */

    //  This parameter shall represent the number of RAM sectors available for
    //  the MCU. calculationFormula = Number of configured McuRamSectorSet-
    //  tingConf
    uint8_t McuRamSectors;

    //  This parameter shall represent the number of clock setting available for
    //  the MCU.
    uint8_t McuClockSettings;

    // This parameter defines the default clock settings that should be used
    // It is an index into the McuClockSettingsConfig
    Mcu_ClockType McuDefaultClockSettings;

    //  This parameter relates to the MCU specific reset configuration. This ap-
    //  plies to the function Mcu_PerformReset, which performs a microcontroller
    //  reset using the hardware feature of the microcontroller.
    //uint32 McuResetSetting;

    //  This container contains the configuration (parameters) for the
    //  Clock settings of the MCU. Please see MCU031 for more in-
    //  formation on the MCU clock settings.
    const McuClockReferencePoint_t * McuClockSettingConfig;

    //  This container contains the configuration (parameters) for the
    //  Mode setting of the MCU. Please see MCU035 for more information
    //  on the MCU mode settings.
    //Mcu_ModeSettingConfigType  *McuModeSettingConfig;

    //  This container contains the configuration (parameters) for the
    //  RAM Sector setting. Please see MCU030 for more information
    //  on RAM sec-tor settings.
    const Mcu_RamSectorSettingConfigType *McuRamSectorSettingConfig;
}Mcu_ConfigType;

#endif /* INCLUDES_MCU_CFG_H_ */
