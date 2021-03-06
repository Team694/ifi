/*******************************************************************************
 * FILE NAME: user_routines.h
 *
 * DESCRIPTION: 
 *  This is the include file which corresponds to user_routines.c and
 *  user_routines_fast.c
 *  It contains some aliases and function prototypes used in those files.
 *
 * USAGE:
 *  If you add your own routines to those files, this is a good place to add
 *  your custom macros (aliases), type definitions, and function prototypes.
 *******************************************************************************/

#ifndef __user_program_h_
#define __user_program_h_


 /*******************************************************************************
                            MACRO DECLARATIONS
 *******************************************************************************/
 /* Add your macros (aliases and constants) here.                              */
 /* Do not edit the ones in ifi_aliases.h                                      */
 /* Macros are substituted in at compile time and make your code more readable */
 /* as well as making it easy to change a constant value in one place, rather  */
 /* than at every place it is used in your code.                               */
 /*
   EXAMPLE CONSTANTS:
   #define MAXIMUM_LOOPS   5
   #define THE_ANSWER      42
   #define TRUE            1
   #define FALSE           0
   #define PI_VAL          3.1415
   
   EXAMPLE ALIASES:
   #define LIMIT_SWITCH_1  rc_dig_int1  (Points to another macro in ifi_aliases.h)
   #define MAIN_SOLENOID   solenoid1    (Points to another macro in ifi_aliases.h)
 */
 
 /* Used in limit switch routines in user_routines.c */
#define OPEN        1     /* Limit switch is open (input is floating high). */
#define CLOSED      0     /* Limit switch is closed (input connected to ground). */
 
/*Joshua's aliases*/

#define OFF 0
#define FORWARD 1
#define REVERSE 2

#define WIND_DOWN_TIME 5000


//Speed constants
#define SERVO_GATE_UP (127+127)
#define SERVO_GATE_DOWN (127)
#define SPIRAL_UP_SPEED (127-127)
#define SPIRAL_DOWN_SPEED (127+127)
#define SPIRAL_OFF_SPEED (127)
#define ACQUISITOR_IN_SPEED (127-127)
#define ACQUISITOR_OUT_SPEED (127+127)
#define ACQUISITOR_OFF_SPEED (127)
#define SHOOTER_FORWARD_SPEED (127-127)

#define FLYWHEEL_VELOCITY 945 // max 29ft/s * 2 = 945in/s
// max = 2*12 m/s = 2*1200 cm/s = 945 in/s 

//Outputs
#define LEFT_DRIVE pwm02
#define RIGHT_DRIVE pwm01
#define SPIRAL pwm07
#define ACQUISITOR pwm04
#define GEARSHIFT pwm05
#define FLYWHEEL pwm08
#define SERVO_GATE pwm12

//Digital sensor inputs
#define R_COUNTER rc_dig_in01
#define L_COUNTER rc_dig_in02
#define FLY_COUNTER rc_dig_in03
#define LOW_GEAR_IN (!rc_dig_in09)
#define HIGH_GEAR_IN (!rc_dig_in08)

//Analog sensor inputs
#define GYRO rc_ana_in01

//Analog OI inputs
#define LEFT_Y p2_y
#define RIGHT_Y p1_y
#define ACQUISITOR_POT p3_y //Not necessarily.
#define SPIRAL_POT p3_x //should be p4_y
#define SHOOTER_POT p4_y
#define AUTONOMOUS_CHOOSER p4_x


//Digital OI inputs
#define AIM_IN (p2_sw_top)
#define REVERSE_INPUT (p1_sw_trig && p2_sw_trig)
#define ACQUISITOR_FWD p3_sw_top
#define ACQUISITOR_REV p3_sw_aux2
#define SPIRAL_UP p3_sw_aux1
#define SPIRAL_DOWN p3_sw_trig
#define SHOOTER_ON p4_sw_trig
#define SERVO_GATE_IN p4_sw_top
//#define SHOOTER_MANUAL p4_sw_aux2

#define GORDON_OVERRIDE (p3_wheel!=127)

//#define ACQUISITOR_SPEED p4_y

/* Motor flips */
#define LEFT_FLIP 0
#define RIGHT_FLIP 1
#define SPIRAL_FLIP 1
#define ACQUISITOR_FLIP 0
#define FLYWHEEL_FLIP 1

#define REVERSE_PWM(x) (255 - (x)) 
 
#define ALLOWABLE_PAN_ERROR 5

#define DEMO_MODE //if this is enabled, when the power rangers switch
		  //is the spiral goes up and down every
		  //SPIRAL_TIME_MS milliseconds.
#ifdef DEMO_MODE
#define SPIRAL_TIME_MS 6000
#endif
 
 /*******************************************************************************
                            TYPEDEF DECLARATIONS
 *******************************************************************************/
 /* EXAMPLE DATA STRUCTURE */
 /*
   typedef struct
   {
   unsigned int  NEW_CAPTURE_DATA:1;
   unsigned int  LAST_IN1:1;
   unsigned int  LAST_IN2:1;
   unsigned int  WHEEL_COUNTER_UP:1;
   unsigned int  :4;
   unsigned int wheel_left_counter;
   unsigned int wheel_right_counter;
   } user_struct;
 */
 
 /*******************************************************************************
                           FUNCTION PROTOTYPES
   *******************************************************************************/
 
 /* These routines reside in user_routines.c */
 void User_Initialization(void);
 void Process_Data_From_Master_uP(void);
 
 /* These routines reside in user_routines_fast.c */
 void InterruptHandlerLow (void);  /* DO NOT CHANGE! */
 void User_Autonomous_Code(void);  /* Only in full-size FRC system. */
 void Process_Data_From_Local_IO(void);
 
 
 
typedef struct
{

   unsigned char motor_R;
   unsigned char motor_L;
   unsigned char motor_F;
   unsigned char motor_A;
   unsigned char motor_S;
		
   float last_out_R;
   float last_out_L;
   float last_out_F;

} robo_out;

typedef struct
{
  
  long rpm_1k_L;
  long rpm_1k_R;
  long rpm_1k_F;
	       
  float vel_L; //inches / sec
  float vel_R;
  float vel_F;
 
  int reverse_drive;
  int shooter;
  int heading;
  int acquisitor;
  int spiral;
  
} robo_target;


typedef struct
{

  //Speeds
  long rpm_1k_L;
  long rpm_1k_R;
  long rpm_1k_F;

  float vel_L; //inches / sec
  float vel_R;
  float vel_F;
  
  //positions of individual parts
  float pos_L; //in inches
  float pos_R; 	
  
  //camera data
  int cam_tracking; //0 if target not seen, !0 if seen
  int cam_pan_angle; //in milliradians

  //position of robot
  int heading; //milliradians

  int shooter;  //FORWARD, OFF
  int acquisitor;  //FORWARD, REVERSE, OFF
  int spiral;  //FORWARD, REVERSE, OFF

  float x_pos;
  float y_pos; //position on field

} robo_state;

void control(robo_state * rs, robo_target * rt, robo_out * ro);
void guidance(robo_state * rs, robo_target * rt);
void output(robo_out * ro);
void update_state( robo_state * rs, robo_target *rt);
void robo_reset( robo_state * rs, robo_target * rt, robo_out *ro);

void Our_Autonomous_Code(void);
void Our_User_Code(void);
void Standard_Drive(robo_state *rs, robo_target *rt, robo_out *ro);
void Demo_Mode(robo_state *rs, robo_target *rt, robo_out *ro);
void LED_Control(void);
void LED_Reset(void);

int abs(int n);
 
#endif
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
