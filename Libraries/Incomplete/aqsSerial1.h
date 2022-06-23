#ifndef AQS_SERIAL1
#define AQS_SERIAL1

enum tSerial1Cmd{
    S1_CMD_INVALID,
    S1_CMD_NONE,
    S1_CMD_HELP_MENU,   // key = <Space>, Print help menu (Context dependent)
    S1_CMD_STATUS,      // key = s or S, Print status info
    S1_CMD_CONFIG,      // key = c or C, Print config settings 
    S1_CMD_MAINT_MODE,  // key = m or M, Go to Maintenance Mode
    S1_CMD_ENTER,       // key = <ENTER>, validate parameters being edited
    S1_CMD_VALVE_OPEN,  // key = o or O, Open the Valve
    S1_CMD_VALVE_CLOSE, // key = k or K, Close the Valve
    S1_CMD_INC_VAL,     // key = p or P, Increment value
    S1_CMD_DEC_VAL,     // key = l or L, Decrement value
    S1_CMD_QUIT,        // key = q or Q, Quit special mode, eg Maintenance Mode
    S1_CMD_NEXT         // key = n or N, go to next parameter to edit
};

class cAqsSerial1 
{
    public:
    public:
        // Constructor
        cAqsSerial1(void);
        // Initialize the class object
        void initSerial1(void);
        // Call service routine regularly to check for received commands
        void serviceSerial1(void);
        // Implement actions related to a Serial1 command
        void actionRxCmd(enum tSerial1Cmd eVal);
        // Get serial commands
        enum tSerial1Cmd getRxCmd(void);
        // Clear the serial command when done servicing it 
        void clearRxCmd(void);
        // send data
    private:
        enum tSerial1Cmd eRxCmd;
        bool bRxCmdValid;
};


#endif
