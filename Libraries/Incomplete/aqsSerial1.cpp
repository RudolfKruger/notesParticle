#include "aqsSerial1.h"
#include "particle.h"
#include "aqsHal.h"

extern cAqsHal aqsHal;

cAqsSerial1::cAqsSerial1(void)
{
    eRxCmd = S1_CMD_NONE;
    bRxCmdValid = false;
}
void cAqsSerial1::initSerial1(void)
{
    Serial1.begin(115200, SERIAL_8N1);
}
void cAqsSerial1::serviceSerial1(void)
{
    static int iRxChar = -1;
    if(Serial1.available())
    {
        iRxChar = Serial1.read();
        switch(iRxChar)
        {
            case ' ':
                eRxCmd = S1_CMD_HELP_MENU;
                bRxCmdValid = true;
                break;
            case 's':
            case 'S':
                eRxCmd = S1_CMD_STATUS;
                bRxCmdValid = true;
                break;
            case 'c':
            case 'C':
                eRxCmd = S1_CMD_CONFIG;
                bRxCmdValid = true;
                break;
            case 'm':
            case 'M':
                eRxCmd = S1_CMD_MAINT_MODE;
                bRxCmdValid = true;
                break;
            case 0x0D: // Enter key
                eRxCmd = S1_CMD_ENTER;
                bRxCmdValid = true;
                break;
            case 'o':
            case 'O':
                eRxCmd = S1_CMD_VALVE_OPEN;
                bRxCmdValid = true;
                break;
            case 'k':
            case 'K':
                eRxCmd = S1_CMD_VALVE_CLOSE;
                bRxCmdValid = true;
                break;
            case 'p':
            case 'P':
                eRxCmd = S1_CMD_INC_VAL;
                bRxCmdValid = true;
                break;
            case 'l':
            case 'L':
                eRxCmd = S1_CMD_DEC_VAL;
                bRxCmdValid = true;
                break;
            case 'q':
            case 'Q':
                eRxCmd = S1_CMD_QUIT;
                bRxCmdValid = true;
                break;
            case 'n':
            case 'N':
                eRxCmd = S1_CMD_NEXT;
                bRxCmdValid = true;
                break;
            default:
                break;
        }
    }
}
enum tSerial1Cmd cAqsSerial1::getRxCmd(void)
{
    if (bRxCmdValid)
    {
        return eRxCmd;
    }
    else
    {
        return S1_CMD_NONE;
    }
}
void cAqsSerial1::clearRxCmd(void)
{
    bRxCmdValid = false;
}
void cAqsSerial1::actionRxCmd(enum tSerial1Cmd eVal)
{
    switch(eVal)
    {
        case S1_CMD_HELP_MENU:
            Serial1.println(">>> AqS Terminal, keypress commands:");
            Serial1.println(" s: Print Status");
            Serial1.println(" c: Print Configuration");
            Serial1.println(" m: Enter maintenance Mode");
            Serial1.println(">>> ");

            Serial1.println(">>> AqS Maintenance mode, keypress commands:");
            Serial1.println(" q: Quit maintenance mode");
            Serial1.println(" s: Print Status");
            Serial1.println(" c: Print Configuration");
            Serial1.println(" n: go to Next parameter to edit"); 
            Serial1.println(" p: Increment value");
            Serial1.println(" l: Decrement value");
            Serial1.println(" <ENTER>: Validate edited parameters");
            Serial1.println(" o: Open valve");
            Serial1.println(" k: Close valve");
            Serial1.println(">>> ");
            
            break;
        case S1_CMD_STATUS:
            Serial1.printlnf(">>> Aqs Status");
            Serial1.println("External Power Supply:");
            if(aqsHal.bExtPowerGood)
            {
                Serial1.println("  ON");
            }   
            else
            {
                Serial1.println("  OFF");
            } 
            Serial1.println("Onboard Power Supply:");
            Serial1.printlnf("  CoinCellBattery : %0.1f Volt", aqsHal.fAdcCoinVBat);
            Serial1.printlnf("  12V Regulator   : %0.1f", aqsHal.fAdc12VMon);
            Serial1.printlnf("  5V Regulator    : %0.1f", aqsHal.fAdc5VMon);
            Serial1.println("CPU Temperature:");
            Serial1.printlnf("  %0.1f degC", aqsHal.fAdcCpuTempC);
            Serial1.println("LiPo Battery:");
            Serial1.printlnf("  %0.1lf Volt", aqsHal.fLipoVoltage);
            Serial1.printlnf("  %0.1lf %% charged", aqsHal.fLipoSoC);
            Serial1.printlnf("  Alert: %u", aqsHal.uiLipoAlert);
            Serial1.println("Flow Meter:");
            Serial1.printlnf(" TotalFlowCnt: %lu",aqsHal.getTotalFlowCnt());
            Serial1.println("Valve: "); 
            Serial1.printlnf("  %0.1f mA", aqsHal.fAdcIValve*1000.0);
            Serial1.println(">>> ");
            break;
        case S1_CMD_CONFIG:
            Serial1.printlnf(">>> Aqs Status");
            Serial1.println(">>> ");
            break;
        case S1_CMD_MAINT_MODE:

            break;
        case S1_CMD_ENTER:
            break;
        case S1_CMD_VALVE_OPEN:
            break;
        case S1_CMD_VALVE_CLOSE:
            break;
        case S1_CMD_INC_VAL:
            break;
        case S1_CMD_DEC_VAL:
            break;
        case S1_CMD_QUIT:
            break;
        case S1_CMD_NEXT:
            break;
        default:
            break;
    }
}