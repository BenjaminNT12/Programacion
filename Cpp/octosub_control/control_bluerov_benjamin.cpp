#include "CJoystick.h"
#include "CJoystick.cpp"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/PoseStamped.h"
#include <std_msgs/Float64MultiArray.h>
#include "sensor_msgs/FluidPressure.h"
#include <std_msgs/Empty.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <fstream>
#include "sensor_msgs/Imu.h"
#include "nav_msgs/Odometry.h"
#include "sensor_msgs/BatteryState.h"						//variable para bateria
#include "geometry_msgs/Quaternion.h"
#include "std_msgs/UInt16.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Bool.h"
#include "tf/tf.h"
#include "tf/tfMessage.h"
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#define PI 3.14159265358979323846
#define g 9.80665   //Aceleracion de la gravedad

using namespace std;

//################# Variables Globales #################
string tt, dvl1, dvl2, dvl3, dato_anterior;
int i = 0, pos4=0, pos1 = 0, pos2 = 0, pos3 =0, b1 = 0, b2 = 0, c = 0, init = 0, init1 = 0, posf, d1=0, d2=0;
float tiempo = 0, T = 0.05;
float tr[8];
float gc[9];  
int B1=0;
int B2=0;
string gr;
ofstream myfile;
ofstream myfile2;
double fluid_press, diff_press, z_baro; 
double posaw, posrollrad, pospitchrad, posyawrad, posroll, pospitch, posyaw;
float posx=0, posy=0, posz, posax, posay, posaz, posroll_p, pospitch_p, posyaw_p;
float pos_x=0, pos_y=0, vel_norte=0, vel_este=0;
double velx,vely,velz,veax,veay,veaz;
double bat, zbf=0.0,zbf_a=0.0, a_z = 0.0;
float zDes, zDes_p, zDes_pp, xDes=1.0, yDes=1.0, rollDes=20.0, pitchDes =10.0;	//Referencias
float yawDes, yawDes_p;
float ex_ant=0,ey_ant=0, ez_ant=0, eyaw_ant=0, eroll_ant=0, epitch_ant=0;	//Valores anteriores
float ex_p=0, eyp=0, ezp=0, eyawp=0, eroll_p=0, epitch_p=0;	//Derivadas
float ex_i=0, ey_i=0, ez_i=0, eyaw_i=0, exx_i=0, eyy_i=0, eroll_i=0, epitch_i=0;	//Derivadas
float chVal=1500,b=100;
float x1, x2, T1, vnort, vest,  VelNorte;
float Xdes_f=0, Ydes_f=0, Xdes_pf=0, Ydes_pf=0, Tf, pfx, pfy; 
float ftt1, ftt2;

float xd, xdp, xdpp, yd, ydp, ydpp, xdp_ant, ydp_ant; //Referencias para trayectoria cuadrada

double Xdeseada, Ydeseada, Xactual, Yactual;
float poss1=0, poss2=0;
//float xd=3, xdp=0, xdpp=0, yd=3, ydp=0, ydpp=0;  //Referencias para trayectoria en x-y, y circular
//float alfa, beta, gamma1, gamma2, K1, K2;
float ux_I, uy_I;
float ux_B, uy_B;
float Ux, Uy, Uz, Uyaw, sigmaX, sigmaY, sigmaZ, sigmaYaw, sigmaRoll, sigmaPitch;
float exx=0, exx_p=0, eyy=0, eyy_p=0, eyaw=0, eyaw_p=0, ez=0, ez_p=0;
float alfa_x, beta_x, gamma1_x, gamma2_x, K1_x, K2_x, alfa_y, beta_y, gamma1_y, gamma2_y, K1_y, K2_y;
float alfa_yaw, beta_yaw, gamma1_yaw, gamma2_yaw, K1_yaw, K2_yaw;
float posxx=0, posyy=0;
float funcion=0, funcion2=0;
float funcion_ant=0, funcion_ant2=0;
float dfuncion=0, dfuncion2=0;
int16_t uposx=0;
int16_t xposxx=0, yposy=0, uxx=0, usxx=0, uyy=0, usyy=0;
//int32_t ux_B=0, uy_B=0;
float kpz=2.50, kiz=0.00, kdz=1.0;  
float Kp_x, Ki_x, Kd_x, Kp_y, Ki_y, Kd_y;
//////Ganancias control robusto  z
float z1z=0.0, z2z=0.0, uz_rob=0.0;
double ctrl_z=0;
//float gN= 10.0, g_roll=1.0;	//solo roll
float gNz= 1.0, g_z=0.30;	//roll y z

float kpz2=9.0, kiz2=0.50, kdz2=3.0;	//Ganancias z PD Saturado
uint16_t uz=0, usz=0;
double zz=0;
bool fl1=0, fl2=0;

float kpx=100.0, kix=5.0, kdx=5.0;	//Ganancias x
float kpx2=100.0, kix2=5.0, kdx2=5.0;	//Ganancias x PD Saturado
uint16_t ux=0, xx=0, uxf=0;

float kpy=100.0, kiy=5.0, kdy=5.0;	//Ganancias y
uint16_t uy=0, yy=0, uyf=0;

float kpyaw , kiyaw , kdyaw ;	//Ganancias yaw
float kpyaw2=1.0, kiyaw2=1.0, kdyaw2=1.0;	//Ganancias yaw PD Saturado
int32_t uyaw=0, yyaw=0, usyaw=0;

float kproll=0.80, kdroll=0.2;	//ganancias para PD robusto con  referencia fija con controlador en z

float kproll2=8.0, kiroll2=1.0, kdroll2=1.40;	//Ganancias roll PD Saturado
uint16_t uroll=0, usroll=0;
double  rroll=0;

//float kppitch=1.0, kipitch=1.0, kdpitch=1.0;	//Ganancias pitch
float kppitch=3.0, kipitch=1.0, kdpitch=1.0;	//Ganancias pitch  PD

float kppitch2=1.0, kipitch2=1.0, kdpitch2=1.0;	//Ganancias pitch PD Saturado
uint16_t upitch=0, ppitch=0, uspitch=0;

//ganancias saturaciones
float b_z = 1, b_yaw = 1;	//Cota de saturacion
float mu_z=0.5, mu_yaw = 0.5;	//Mu entre 0 y 1

int paro=0,  bajar=0,  armar=0,   control_pos= 0,   desarmar=0, controles=0;
int forwardmove=0, lateralmove=0;
int axis_frwd, axis_latr, axis_vrtl, axis_yaw, axis_roll, axis_pitch;
int satkpz=0, satkiz=0, satkdz=0;
int satkproll=0, satkiroll=0, satkdroll=0;
int satkppitch=0, satkipitch=0, satkdpitch=0;
int satkpyaw=0, satkiyaw=0, satkdyaw=0, satkpx=0, satkix=0, satkdx=0, satkpy=0, satkiy=0, satkdy=0;
int satxx =0, satyy=0;

//Ganancias control robusto
float z1roll=0.0, z2roll=0.0, uroll_rob=0.0;
double ctrl_roll=0;
//float gN= 10.0, g_roll=1.0;	//solo roll
float gN= 10.0, g_roll=1.8;	//roll y z
int Tp;

float satura(float a);  //Definicion de funcion
float saturayaw(float c);  //Definicion de funcion
float saturob(float c);
float saturaposxx(float c);
float saturaposyy(float c);
int satK(float h, float b, float k, float m);
int sgn(float in);
int Sat(float S, float varsigma);

//Variables para trayectoria
int t=0, us=0, signo=0, elem=0, r=0;
float tiempo2=0, tiempo3=0, paso=0.05, valor=0;
float tfinal=60,  z_filter_ant=0, t_eje=75;
float roll_filter_ant=0, pitch_tray_ant=0, pitch_filter_ant=0;
float t1=0.0;
float valsin=0, intsin=0;
int chValz=1480;
time_t currentTime = time(0);

std_msgs::Bool armState;
std_msgs::String modo;
std::stringstream motxt;
std::stringstream filenameDate;

std_msgs::UInt16 vertical;
std_msgs::UInt16 lateral;
std_msgs::UInt16 fforward;
std_msgs::UInt16 yaw;
std_msgs::UInt16 roll;
std_msgs::UInt16 pitch;

std_msgs::UInt16 verticalc;
std_msgs::UInt16 lateralc;
std_msgs::UInt16 fforwardc;
std_msgs::UInt16 yawc;
std_msgs::UInt16 xxc;
std_msgs::Int16 u_F;
std_msgs::Int16 u_L;
std_msgs::UInt16 yyc;
std_msgs::UInt16 rollc;
std_msgs::UInt16 pitchc;

string dato;

//################# Funciones Callback #################
//Orientación vehiculo real (Roll, Pitch, Yaw)       				%%%%%%%%%%%
// Función para manejar los mensajes de posición recibidos
void posCallback(const sensor_msgs::Imu::ConstPtr & msg) 
{
    // Extraer los componentes de la orientación del mensaje
    posax = msg->orientation.x; 
    posay = msg->orientation.y;
    posaz = msg->orientation.z;
    posaw = msg->orientation.w;

    // Extraer los componentes de la velocidad angular del mensaje
    posroll_p = msg->angular_velocity.x;
    pospitch_p = msg->angular_velocity.y;
    posyaw_p = msg->angular_velocity.z;

    // Extraer la velocidad angular en el eje x
    veax = msg->angular_velocity.x;

    // Crear un cuaternión a partir de los componentes de la orientación
    tf::Quaternion q(posax, posay, posaz, posaw);

    // Convertir el cuaternión a una matriz de rotación
    tf::Matrix3x3 m(q);

    // Obtener los ángulos de rotación (roll, pitch, yaw) de la matriz
    m.getRPY(posrollrad, pospitchrad, posyawrad);

    // Convertir los ángulos de radianes a grados
    posroll = posrollrad * (180 / PI);
    pospitch = -1 * (pospitchrad * (180 / PI));

    // Convertir el ángulo de yaw de radianes a grados
    posyaw = posyawrad * (180 / PI);

    // Si el ángulo de yaw es positivo, restarle 360
    if (posyaw > 0)
    {
        posyaw = posyaw - 360;
    };
}

// Función para manejar los mensajes de odometría recibidos
void odomCallback(const nav_msgs::Odometry::ConstPtr & msg) 
{
    // Extraer la información de posición del mensaje de Odometría
    posx = msg->pose.pose.position.x;
    posy = msg->pose.pose.position.y;
    posz = msg->pose.pose.position.z;

    // Imprimir la información de posición a la consola (opcional)
    //ROS_INFO("Position: x=%.3f, y=%.3f, z=%.3f", posx, posy, posz);
    //ROS_INFO_STREAM("Datos: " << posx  << endl);
}

// Función para manejar los mensajes de presión de fluidos recibidos
void presCallback(const sensor_msgs::FluidPressure::ConstPtr & msg) 
{
    // Extraer la presión del fluido y la varianza del mensaje
    fluid_press = msg->fluid_pressure;
    diff_press = msg->variance;

    // Calcular z_baro a partir de la presión del fluido
    z_baro = fluid_press - 802.6;

    // Calcular el coeficiente de filtrado a_z
    a_z = 0.1061;

    // Calcular la z filtrada
    zbf = a_z * z_baro + (1 - a_z) * zbf_a;

    // Actualizar zbf_a para la próxima iteración
    zbf_a = zbf;
}

//################# CICLO PRINCIPAL #################
int main(int argc, char **argv)
{
	ros::init(argc, argv, "dvl_subscriber");
  	ros::NodeHandle n;
  	ros::NodeHandle nh;
  	ros::Subscriber sub = n.subscribe("dvl_out", 10, chatterCallback);


	ros::init(argc, argv, "publisher");
    ros::Publisher number1_pub = nh.advertise<std_msgs::Float32>("Xdeseada", 10);
	ros::Publisher number2_pub = nh.advertise<std_msgs::Float32>("Ydeseada", 10);
	ros::Publisher number3_pub = nh.advertise<std_msgs::Float32>("Xactual", 10);
	ros::Publisher number4_pub = nh.advertise<std_msgs::Float32>("Yactual", 10);

    //ros::Rate loop_rate(1); // Publicar un mensaje por segundo


	tm* currentDate = localtime(&currentTime);
  	ros::init(argc, argv, "octosub_node");
	ros::Subscriber subPres;
	ros::Subscriber subBat;

	ros::Publisher pubArm;
	ros::Publisher pubMod;

	//Movimientos
	ros::Publisher pubVertical;
	ros::Publisher pubLateral;
	ros::Publisher pubForward;
	ros::Publisher pubYaw;
	ros::Publisher pubRoll;
	ros::Publisher pubPitch;

	CJoystick *H = new CJoystick();

  	//#################Generar archivo para guardar los datos del DVL##############
  	int archivo;
  	ifstream last_file;
	last_file.open ("/home/cesar/BlueROV2_ws/src/reading_dvl/src/Datos-DVL/lastlog.txt");
	last_file >> archivo;
	last_file.close();

	char str1[80];
	snprintf (str1,80,"/home/cesar/BlueROV2_ws/src/reading_dvl/src/Datos-DVL/data_dvl%d.txt",archivo);

	ofstream last_file1;
	last_file1.open ("/home/cesar/BlueROV2_ws/src/reading_dvl/src/Datos-DVL/lastlog.txt");
	archivo++;
	last_file1 << archivo;
	last_file1.close();

	ofstream myfile;
  	char str2[80];
	snprintf (str2,80,"/home/cesar/BlueROV2_ws/src/reading_dvl/src/Datos-DVL/data_dvl%d.txt",archivo-1);
	myfile.open (str2); // ARCHIVO DONDE SE GUARDAN LOS DATOS DEL UAV1

	//#################Generar archivo para guardar los datos de la IMU##############
  	int archivo2;
  	ifstream last_file2;
	last_file2.open ("/home/cesar/BlueROV2_ws/src/reading_dvl/src/Datos-IMU/lastlog.txt");
	last_file2 >> archivo2;
	last_file2.close();

	char str3[80];
	snprintf (str3,80,"/home/cesar/BlueROV2_ws/src/reading_dvl/src/Datos-IMU/data_imu%d.txt",archivo2);

	ofstream last_file3;
	last_file3.open ("/home/cesar/BlueROV2_ws/src/reading_dvl/src/Datos-IMU/lastlog.txt");
	archivo2++;
	last_file3 << archivo2;
	last_file3.close();

	ofstream myfile2;
  	char str4[80];
	snprintf (str4,80,"/home/cesar/BlueROV2_ws/src/reading_dvl/src/Datos-IMU/data_dvl%d.txt",archivo2-1);
	myfile2.open (str4); // ARCHIVO DONDE SE GUARDAN LOS DATOS DEL UAV1

  	//Nodo
  	ros::Subscriber subPos;
	ros::Subscriber odomPos;
  	//################# Subscriptores #################
  	subPos  = nh.subscribe("/BlueRov2/imu/data",1, posCallback);  //Topico real
	odomPos  = nh.subscribe("/BlueRov2/odometry",1, odomCallback);  //Topico real

  	pubVertical=nh.advertise<std_msgs::UInt16>("BlueRov2/rc_channel3/set_pwm", 1);
  	pubLateral=nh.advertise<std_msgs::UInt16>("BlueRov2/rc_channel6/set_pwm", 1);
  	pubForward=nh.advertise<std_msgs::UInt16>("BlueRov2/rc_channel5/set_pwm", 1);
  	pubYaw=nh.advertise<std_msgs::UInt16>("BlueRov2/rc_channel4/set_pwm", 1);
  	pubRoll=nh.advertise<std_msgs::UInt16>("BlueRov2/rc_channel2/set_pwm", 1);
  	pubPitch=nh.advertise<std_msgs::UInt16>("BlueRov2/rc_channel1/set_pwm", 1);

  	ros::Subscriber Joystick = nh.subscribe("joy", 1000, &CJoystick::chatterCallback,H);

  	//################# Publicadores #################
  	//Armar
  	pubArm=nh.advertise<std_msgs::Bool>(nh.resolveName("/BlueRov2/arm"), 1);

  	//Modo deph hold
  	pubMod=nh.advertise<std_msgs::String>(nh.resolveName("/BlueRov2/mode/set"), 1);
  	motxt << "manual";
  	modo.data=motxt.str();
	ros::Rate loop_rate(20);


  	
	while (ros::ok())
  	{	
		//################# Publicar datos de la IMU ##############
		// Xdeseada = xd; 
		// std_msgs::Float32 msg;
        // msg.data = Xdeseada;
        // number1_pub.publish(msg);
		
		// Ydeseada = yd; 
        // msg.data = Ydeseada;
        // number2_pub.publish(msg);

		// Xactual = posxx; 
        // msg.data = Xactual;
        // number3_pub.publish(msg);
		
		// Yactual = posyy; 
        // msg.data = Yactual;
        // number4_pub.publish(msg);

        //ROS_INFO("Number_X: %.2f", number1);
		//ROS_INFO("Number_Y: %.2f", number2);
		
		//##################### Calcular pos1 and pos2 #####################
		// if (abs(tr[5]) > 0.1)
		// {
		// 	poss1 = posxx;
		// }
		// else 
		// 	posxx = posxx + tr[5];
		
		// if (abs(tr[6]) > 0.1)
		// {
		// 	poss2 = posyy;
		// }
		// else
        // 	posyy = posyy + tr[6];	
		
		//funcion = posxx;
		// funcion = posx;				//comentar si se hacen pruebas reales con el DVL
    	// dfuncion = (funcion - funcion_ant)/(0.05);
		// funcion_ant = funcion;
		// vnort = dfuncion;

		// //funcion2 = posyy;
		// funcion2 = posy;			//comentar si se hacen pruebas reales con el DVL
    	// dfuncion2 = (funcion2 - funcion_ant2)/(0.05);
		// funcion_ant2 = funcion2;
		// vest = dfuncion2;

		//Funciones de joystick
        // Asignación de comandos a variables
        armar = H->a;
        control_pos = H->b;
        desarmar = H->y;
        paro = H->x;
        forwardmove = H->b5;
        lateralmove = H->b6;

        // Manipulación de roll y pitch
        axis_latr = 1500 + (H->JYaw * 200) * 0.5;
        axis_frwd = 1500 + (H->JGaz * 200) * 0.5;
        axis_vrtl = 1500 - (H->JPitch * 200) * 0.5;
        axis_yaw = 1500 + (H->JRoll * 50);
        axis_roll = 1500;
        axis_pitch = 1500;

        // Asignación de valores de joystick a variables para publicación en tópicos de ROS
        vertical.data = axis_vrtl;
        lateral.data = axis_latr;
        fforward.data = axis_frwd;
        yaw.data = axis_yaw;
        roll.data = axis_roll;
        pitch.data = axis_pitch;

		//Alarma bateria baja
		if(bat<=13.4)
    	{
			//printf("BATERIA BAJA\n");
		} 

		if(armar==true)	//boton a
    	{
			printf("Armado\n");
			armState.data=true;
	  	  	pubArm.publish(armState);
		}

    	if(desarmar==true)	//boton y
    	{
			printf("Desarmado\n");
			armState.data=false;
	    	pubArm.publish(armState);
    	}

		if(paro==true)	//boton x
    	{
			printf("Paro\n");
			controles=false;
			vertical.data=1500;
			lateral.data=1500;
			fforward.data=1500;
			yaw.data=1500;
			roll.data=1500;
			pitch.data=1500;

	    	pubVertical.publish(vertical);
	    	pubLateral.publish(lateral);
	    	pubForward.publish(fforward);
	    	pubYaw.publish(yaw);
			pubRoll.publish(roll);
			pubPitch.publish(pitch);
			armState.data = false;
	    	pubArm.publish(armState);

			return 0;
    	}
		if(forwardmove==true)	//boton b5
		{
			//controles=true;
			posxx=0;
			//for (tiempo3=0; i < 50; i++)
			//fforward.data=1500+100;
	    	//pubForward.publish(fforward);
			//B1=1;
		}
		else
		{
			B1=0;
		}
		if(lateralmove==true) //boton b6
		{
			//printf("Lateral_move\n");
			controles=true;
			lateral.data=1500+100;
	    	pubLateral.publish(lateral);
			B2=1;
		}
		else
		{
			B2=0;
		}
    	//Boton de constrol activa una bandera para el ciclo de control que se ejecuta durante cierto tiempo
	  	if(control_pos==true)	//boton b
	  	{	
			printf("Control\n");
			// myfile <<  " Control \n";
			controles=true;
			//posxx = 0;
			//posyy = 0;
			//actualiza referncia yaw
			//yawDes=posyaw;
	  	}
		//################# CICLO DEL CONTROLADOR #################
	  	if(controles == true)
	  	{
			tiempo2=tiempo2+0.05;	//tiempo
			
			
			Tf = 60;	// Tiempo de trayectoria cuadrada
			
			pfx = 3;	//Trayectoria lineal
			
			//################# INICIA EL CONTROLADOR #################
			//######################       PID     ###################
			//##################### Control de Yaw ###################
			kpyaw=0.5, kiyaw=0.01, kdyaw=0.25;  
			yawDes = -145.0;
			yawDes_p = 0.0;
			
			eyaw =  posyaw - yawDes;  	
			
			if (eyaw > 10)	
				eyaw = 10;
			if (eyaw < -10)
				eyaw = -10;
			
			eyaw_p = posyaw_p - yawDes_p;											

			eyaw_i = eyaw_i + (eyaw*0.05);
			
			yyaw = -( kpyaw*eyaw + kdyaw*eyaw_p + kiyaw*eyaw_i);							
					
			if (yyaw >= 0)
				uyaw=(1510+yyaw);
			else 
				uyaw=(1490+yyaw);
														
			usyaw=saturayaw(uyaw);	//Satura la señal de pwm entre 1100 a 1900
			
			yawc.data=usyaw; 

			//################## Control en Z #################
			int amp=60, perd =60;
			int amp2=10, perd2 =60;
			float a1= (2*PI/perd);
			float a2= (2*PI/perd2);
			
			
			kpz=2.50, kiz=0.00, kdz=1.0;
			//coseno
			zDes = 20 + amp2 * cos( a2*tiempo ); 
			zDes_p = -a2*amp2 *sin( a2*tiempo ); 
			zDes_pp = - ((a2)*(a2))*amp2 * cos( a2*tiempo );

			ez=z_baro-zDes;  									//Error  ref coseno
			ez_p=(ez-ez_ant)/0.05;														//Error p gyro
			ez_i=ez_i+(ez*0.05);
			ez_ant=ez;
			
			zz= -( kpz*ez+kdz*ez_p+ez_i*kiz );	// Controlador PID

			usz=satura(zz);														//Satura la señal de pwm entre 1100 a 1900
			verticalc.data=usz;													//se envia valor saturado
			
			
			Kp_x=9, Ki_x=0.01, Kd_x=0.15;  
			
			Kp_y=5, Ki_y=0.01, Kd_y=0.15;
			
			xd = 3;
			xdp =0;

			exx = ( posxx - xd );
			int ox=1;
			if (exx > ox)    
			    exx = ox;
			if (exx < -ox)
			    exx = -ox;                              

			exx_p = ( vnort - xdp );
			exx_i = exx_i + (exx*0.05);                      
			
			yd = 0;
			ydp = 0;

			eyy = ( posyy - yd );
			int oy=1; 
			if (eyy > oy)    
			    eyy = oy;
			if (eyy < -oy)
			    eyy = -oy;                              

			eyy_p = ( vest - ydp );
			eyy_i = eyy_i + (eyy*0.05);

			ux_B = -( Kp_x*exx + Kd_x*exx_p + Ki_x*exx_i ); 
			uy_B = -( Kp_y*eyy + Kd_y*eyy_p + Ki_y*eyy_i );


			// Matriz de rotación
			ux_I = ux_B*cos(posyaw*3.141592/180) + uy_B*sin(posyaw*3.141592/180);
			uy_I = -ux_B*sin(posyaw*3.141592/180) + uy_B*cos(posyaw*3.141592/180);

			if (ux_I >= 0 )
				uxx=(1515+ux_I);	
			else
			uxx=(1485+ux_I);																				
			usxx=saturaposxx(uxx);								
			u_F.data=usxx;										

			if (uy_I >= 0 )
				uyy=(1515+uy_I );	
			else
				uyy=(1485+uy_I);			
			usyy=saturaposyy(uyy);								
			u_L.data=usyy;

			//pubForward.publish(u_F);
			//pubLateral.publish(u_L);
			pubVertical.publish(verticalc);
			pubYaw.publish(yawc);



	  	}
	  	else
	  	{
			// MODO DE OPERACION MANUAL
	    	pubVertical.publish(vertical);
	    	pubLateral.publish(lateral);
	    	pubForward.publish(fforward);
	    	pubYaw.publish(yaw);
		  	pubRoll.publish(roll);
		  	pubPitch.publish(pitch);
			//ROS_INFO_STREAM("Mensaje: " << "Holaa" << endl) ;

	  	}


		ROS_INFO_STREAM("DatosPos_Z: " << tiempo2  << "\t" << ez  << "\t" << zz << "\t" << usz << "\t" << posz << "\t" << zDes  << endl);
		
	
		myfile << std::setprecision(5) << tiempo2 << "\t" << xd << "\t" << yd << "\t" << zDes << "\t" << yawDes << "\t" << posxx << "\t" << posyy << "\t" << posz << "\t" << posyaw << "\t" << ux_B << "\t" << uy_B << "\t" << usxx << "\t" << usyy << "\n";
      	//##########################Lectura de datos para el mensaje tipo: $DVPDL###################
		

		ros::spinOnce();
      	loop_rate.sleep();
      	tiempo = tiempo + T;
      	
  	} //FIN DEL WHILE
  
  delete H;
  return 0;
  myfile.close();
  myfile2.close();
} 

