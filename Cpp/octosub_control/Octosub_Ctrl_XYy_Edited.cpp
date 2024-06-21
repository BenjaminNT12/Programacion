#include <stdio.h>
#include <ctime>
#include "tf2/LinearMath/Quaternion.h"
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;



//################# Variables Globales #################
double fluid_press, diff_press,z_baro, bat;
double velx,vely,velz,veax,veay,veaz;
double posx, posy, posz, posax, posay, posaz, posaw, posrollrad, pospitchrad, posyawrad, posroll, pospitch, posyaw;
double  poszedx, poszedy, poszedz;
float zDes=20.0, xDes=1.0, yDes=1.0, yawDes=0.0, rollDes=20.0, pitchDes =10.0;  				//Referencias


float ez=0, ex=0,  ey=0, eyaw=0, eroll=0, epitch=0;												//Errores
float ex_ant=0,ey_ant=0, ez_ant=0, eyaw_ant=0, eroll_ant=0, epitch_ant=0;   //Valores anteriores
float ex_p=0, ey_p=0, ez_p=0, eyaw_p=0, eroll_p=0, epitch_p=0;						//Derivadas
double ex_i=0, ey_i=0, ez_i=0, eyaw_i=0, eroll_i=0, epitch_i=0;	
//Señales de control
double ctrl_z=0, ctrl_x=0, ctrl_y=0, ctrl_roll=0, ctrl_pitch=0, ctrl_yaw=0;
int16_t uz=0, usz=0, ux=0, usx=0, uy=0, usy=0, uroll=0, usroll=0, upitch=0, uspitch=0, uyaw=0, usyaw=0;
double zz=0, xx=0, yy=0, rroll=0, ppitch=0, yyaw=0;

//Constantes
float chVal=1500,b=100;

//ganancias saturaciones
float b_z = 1, b_yaw = 1;             											//Cota de saturacion
float mu_z=0.5, mu_yaw = 0.5;  												//Mu entre 0 y 1

int paro=0,  bajar=0,  armar=0,   control_pos= 0,   desarmar=0, controles=0;
int axis_frwd, axis_latr, axis_vrtl, axis_yaw, axis_roll, axis_pitch;
int satkpz=0, satkiz=0, satkdz=0;
int satkproll=0, satkiroll=0, satkdroll=0;
int satkppitch=0, satkipitch=0, satkdpitch=0;
int satkpyaw=0, satkiyaw=0, satkdyaw=0;

///Ganancias Sliding
float bett1_w1=1, bett1_w2=1, bett1_w3=1, bett1_w4=1, bett1_v1=1, bett1_v2=1, bett1_v3=1, bett1_v4=1;
float bett2_w1=1, bett2_w2=1, bett2_w3=1, bett2_w4=1, bett2_v1=1, bett2_v2=1, bett2_v3=1, bett2_v4=1;
float gamm1_w1=1, gamm1_w2=1, gamm1_w3=1, gamm1_w4=1, gamm1_v1=1, gamm1_v2=1, gamm1_v3=1, gamm1_v4=1;
float gamm2_w1=1, gamm2_w2=1, gamm2_w3=1, gamm2_w4=1, gamm2_v1=1, gamm2_v2=1, gamm2_v3=1, gamm2_v4=1;

//bett3 = Inv(bett_w2) + Inv(bett_v2); //obtener la inversa de los elementos
//gamm3 = Inv(gamm_w2) + Inv(gamm_v2); //obtener la inversa de los elementos
// float bett3_w1=1, bett3_w2=1, bett3_w3=1, bett3_w4=1, bett3_v1=1, bett3_v2=1, bett3_v3=1, bett3_v4=1;
// float gamm3_w1=1, gamm3_w2=1, gamm3_w3=1, gamm3_w4=1, gamm3_v1=1, gamm3_v2=1, gamm3_v3=1, gamm3_v4=1;
float bett3_w1=1/bett2_w1, bett3_w2=1/bett2_w2, bett3_w3=1/bett2_w3, bett3_w4=1/bett2_w4, bett3_v1=1/bett2_v1, bett3_v2=1/bett2_v2, bett3_v3=1/bett2_v3, bett3_v4=1/bett2_v4;
float gamm3_w1=1/gamm2_w1, gamm3_w2=1/gamm2_w2, gamm3_w3=1/gamm2_w3, gamm3_w4=1/gamm2_w4, gamm3_v1=1/gamm2_v1, gamm3_v2=1/gamm2_v2, gamm3_v3=1/gamm2_v3, gamm3_v4=1/gamm2_v4;


//Dual I_3x3 = I_3x3 + E I_3x3
float Iw1=1, Iw2=1, Iw3=1, Iw4=1, Iv1=1, Iv2=1, Iv3=1, Iv4=1;

//Variables vectores y matrices
Vector3f v_ve, v_le_dot, v_w_e, v_le; 
//////////////Definicion de variables quaternion//////////////
tf2::Quaternion q_tr(0,0,0,1);
float radio[3]={0.7,0,0}, xyz[3]={0.7,0,0}, qd_dot[4], qPId_dot[4], le[3], le_dot[3], qe_dot[4], w[3], we[3]; 
float le_ant[3], qe_ant[4], qd_ant[4] , qPId_ant[4], ve[3];
float eqe_w1=0, eqe_w2=0, eqe_w3=0, eqe_w4=0, eqe_v1=0, eqe_v2=0, eqe_v3=0, eqe_v4=0;
float exie_w1=0, exie_w2=0, exie_w3=0, exie_w4=0, exie_v1=0, exie_v2=0, exie_v3=0, exie_v4=0;
float s_w1=0, s_w2=0, s_w3=0, s_w4=0, s_v1=0, s_v2=0, s_v3=0, s_v4=0;
float p_w1=0, p_w2=0, p_w3=0, p_w4=0, p_v1=0, p_v2=0, p_v3=0, p_v4=0;

//float kp_w1=0, kp_w2=0, kp_w3=0, kp_w4=0, kp_v1=0, kp_v2=0, kp_v3=0, kp_v4=0;
//float kd_w1=0, kd_w2=0, kd_w3=0, kd_w4=0, kd_v1=0, kd_v2=0, kd_v3=0, kd_v4=0;
float pd_w1 = 0, pd_w2 = 0, pd_w3 = 0, pd_w4 = 0, pd_v1 = 0, pd_v2 = 0, pd_v3 = 0, pd_v4 = 0;
		
	
tf2::Quaternion q_d(0,0,0,1), q_d_dot, q_pos(0, 0, 0, 1);
tf2::Quaternion q_PId, q_PI, q_res, q_rad, q_e(0,0,0,1), l_e, q_PId_dot, q_e_dot, Theta_e, q_w, w_e;
tf2::Quaternion D_e_q_e_w, D_e_q_e_v, q_xi_e_w, q_xi_e_v, D_e_xi_e_w, D_e_xi_e_v;
tf2::Quaternion q_pw, q_pv,  Tw_in, Tv_in, q_PI_PId, q_pdw, q_pdv;
tf2::Quaternion q_imu, q_trl;

tf2::Quaternion q_otro(0, 0, 1, 0), q_r(0.7, 0, 0, 0); //quaternion radio 2m
	


//################# Funciones Definidas #################

float satura(float a);  

float saturayaw(float c);  									//Definicion de funcion

float saturob(float c);

tf2::Quaternion qNorm(tf2::Quaternion q_in4);

tf2::Quaternion qConj(tf2::Quaternion q_in);

tf2::Quaternion qLn(tf2::Quaternion q_in2);

tf2::Quaternion q2_x(tf2::Quaternion q_in3);

float offset(float d);											//Ofset zona muerta de motores

int satK(float h, float b, float k, float m); 

int sgn(float in);													//Funcion signo

//################# Funciones Callback #################
//Orientación vehiculo real
void posCallback(const sensor_msgs::Imu::ConstPtr & msg) {
     posax=msg->orientation.x;
	 posay=msg->orientation.y;
	 posaz=msg->orientation.z;
	 posaw=msg->orientation.w;
	 
		q_imu.setW( posaw); //***
		q_imu.setX( posax);
		q_imu.setY( posay);
		q_imu.setZ( posaz);	
		
		q_imu = qNorm(q_imu);
		
	 veax=msg->angular_velocity.x;
	 veay=msg->angular_velocity.y;
	 veaz=msg->angular_velocity.z;
	 
	 tf::Quaternion q(posax, posay, posaz, posaw);
     tf::Matrix3x3 m(q);
     m.getRPY(posrollrad,pospitchrad,posyawrad);
	 
	// ROS_INFO( "posaw%.3f,", msg->orientation.x);
	 
	 posyaw=posyawrad*(180/PI);
	 posroll=posrollrad*(180/PI);	 
	 pospitch=pospitchrad*(180/PI)-3.5;	
}




//################# CICLO PRINCIPAL #################

int main(int argc, char **argv)
{
	//Variables para trayectoria definida desde el inicio
	int t=0, us=0, signo=0, elem=0, r=0;
	float tiempo=0, paso=0.05, valor=0;
	float tfinal=300,  t_eje=120;      //tfinal > t_eje  
	float t1=0.0;
	bool flg=0;
	

	
	//VARIABLES DE FILTRO PARA LA TRAYECTORIA
	float rc = 8, a=0;     //Rc aproxima al valor de convergencia de la señal filtrada
	a = 1/(1*PI*rc);
	
	elem=tfinal/paso;    //calcula los elementos del vector de trayectoria
	
	float tt[elem], z_tray[elem],  x_tray[elem], y_tray[elem], z_filter[elem], x_filter[elem], y_filter[elem];
	float roll_tray[elem], roll_filter[elem], pitch_tray[elem], pitch_filter[elem], yaw_tray[elem], yaw_filter[elem];
	//Referencias puntos para control de estabilizacion
	float ref_p_roll[elem], ref_p_z[elem], ref_p_x[elem], ref_p_y[elem];
	
	float yd=0, xd=0;
	
	//Variables para filtrar referencias 
	
	float roll_filter_ant=0, pitch_filter_ant=0, yaw_filter_ant=0, z_filter_ant=0, x_filter_ant=0, y_filter_ant=0; 
	float pitch_tray_ant=0;
	
	//Genera vextor de tiempo para trayectoria
	tt[0]=0;

	
	//Genera trayectorias 
	z_tray[0]=0;
	x_tray[0]=0;
	y_tray[0]=0;
	roll_tray[0]=0;
	pitch_tray[0]=0;
	yaw_tray[0]=0;
	

	

	float valsin=0, intsin=0;
	int chValz=1480;
	
	time_t currentTime = time(0);
	tm* currentDate = localtime(&currentTime);
	
	filenameDate << "/home/samantha/catkin_ws/src/codigo/src/Data/OctoCtrlXYyZED"<< currentDate->tm_mday<<"_"<<currentDate->tm_mon+1<< "_"<<currentDate->tm_year+1900<<"-"<< currentDate->tm_hour<< "_"<<currentDate->tm_min<< "_"<<currentDate->tm_sec<<".txt";

	//Generacion de archivo para guardar variables
	ofstream myfile;
	//myfile.open("/home/salatiel/catkin_ws/src/codigo/src/Data/BlueRovPD.txt");    //ruta del archivo
	myfile.open(filenameDate.str());    //ruta del archivo
	
	ros::init(argc, argv, "octosub_node");
	ros::NodeHandle nh;
	

	float offsetx=0, offsety=0;
 

	
	if(armar==true)  //Boton A armado
    {
		printf("Armado\n");
		armState.data=true;
	    pubArm.publish(armState);
		flg = true;
		offsetx =poszedx;
		 offsety =poszedy;
	}
	 
	
	if(paro==true)  //Boton X paro de control y codigo
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
		
		armState.data=false;
	    pubArm.publish(armState);
		
		offsetx =0;
		offsety =0;
		
		return 0;
    }
	

	
	//////////////GANANCIAS PARA PID /////////////////
	float kpz=1.5, kiz=0.00, kdz=0.5;  										//Ganancias z
	float kpy=100.0, kiy=5.0, kdy=5.0; 									//Ganancias y
	float kpx=100.0, kix=5.0, kdx=5.0; 									//Ganancias x
	//float kpyaw=1.0, kiyaw=1.0, kdyaw=0; 							//Ganancias yaw
	float kpyaw=0.025, kiyaw=1.0, kdyaw=0.05; 							//Ganancias yaw	
	float kproll=0.70, kdroll=0.150, kiroll=0.0;  						//Ganancias roll
	float kppitch=3.0, kipitch=1.0, kdpitch=1.0; 						//Ganancias pitch
	
	//tryectoria quat 
	float gamma=2*PI/30;
	
	//ganancias pd quaternion
	//							2roll				3pitch		4yaw           				2x			3y 	  		4z
	float kp_w1=1, kp_w2=1, kp_w3=1, kp_w4=400, kp_v1=1, kp_v2=200, kp_v3=30, kp_v4=1;
	float kd_w1=1, kd_w2=1, kd_w3=1, kd_w4=1, kd_v1=1, kd_v2=1, kd_v3=1, kd_v4=1;
	
	//ganancias smc quaternion
	//	2roll		3pitch		4yaw           	2x		3y 	  	4z
	float kw1=1, 	kw2=1, 	kw3=1, 	kw4=1,	 kv1=1, 	kv2=1, 	kv3=1 ,	 kv4=1;
	float K1_w1=1, K1_w2=1, K1_w3=1, K1_w4=10, K1_v1=1, K1_v2=1, K1_v3=1, K1_v4=1;
	float K2_w1=1, K2_w2=1, K2_w3=1, K2_w4=5, K2_v1=1, K2_v2=1, K2_v3=1, K2_v4=1;
	
	//##########  CICLO PRINCIPAL DEL DEL CONTROLADOR ##########//	 
	
	if(controles == true) 
	{ 
		tiempo=tiempo+0.05;   							//Calculo de tiempo
			
	if(tiempo<=t_eje)   //Condiciona el controlador a un tiemo de ejecucion: t_eje, o un tiempo maximo correspondiente a la duracion de la trayectoria generada: tfinal
		{
			
			///CUATERNION DEL SISTEMA
			// q_PI.setX( poszedx);
			// q_PI.setY( poszedy);
			// q_PI.setZ( z_baro);
			
			//Trayectoria en quaternion 
			 q_trl.setW( cos((gamma*tiempo)/2));
			 q_trl.setX( 0);
			 q_trl.setY( 0);
			 q_trl.setZ( sin((gamma*tiempo)/2));
			
			//Derivada q_d
			qd_dot[0]=( q_d.getW() - qd_ant[0])/0.5;
			qd_dot[1]=( q_d.getX() - qd_ant[1])/0.5;
			qd_dot[2]=( q_d.getY() - qd_ant[2])/0.5;
			qd_dot[3]=( q_d.getZ() - qd_ant[3])/0.5;
			
			q_d_dot.setW(qd_dot[0]);
			q_d_dot.setW(qd_dot[1]);
			q_d_dot.setW(qd_dot[2]);
			q_d_dot.setW(qd_dot[3]);
			
			q_PId=q_d*(q_r * qConj(q_trl))+(q_otro-q_r); 
			//q_PId.setY(0);

			//Derivada q_PId
			qPId_dot[0]=( q_PId.getW() - qPId_ant[0])/0.5;
			qPId_dot[1]=( q_PId.getX() - qPId_ant[1])/0.5;
			qPId_dot[2]=( q_PId.getY() - qPId_ant[2])/0.5;
			qPId_dot[3]=( q_PId.getZ() - qPId_ant[3])/0.5;	

			q_PId_dot.setW(qPId_dot[0]);
			q_PId_dot.setW(qPId_dot[1]);
			q_PId_dot.setW(qPId_dot[2]);
			q_PId_dot.setW(qPId_dot[3]);		
		
			
			//sustraccion de  (q_PI-q_PId)
			q_PI_PId.setW(0);
			q_PI_PId.setX( (poszedx-offsetx)*4 - q_PId.getX() );
			q_PI_PId.setY( (poszedy-offsety)*4 - q_PId.getY());
			q_PI_PId.setZ( z_baro - q_PId.getZ());
			
			// ***Suma y resta de cuaterniones : elemento x elemento***
			//l_e = qConj(q_imu) * (q_PI_PId * q_imu); 
			l_e = qConj(q_e) * (q_PI_PId * q_e); 
			
			//vector le
			le[0]= l_e.getX();
			le[1]= l_e.getY();
			le[2]= l_e.getZ();
			
			v_le(0) = l_e.getX();  //Representacion en vector3f
			v_le(1)= l_e.getY();
			v_le(2)= l_e.getZ();
			
			//derivada le
			le_dot[0]=(le[0]-le_ant[0])/0.05;
			le_dot[1]=(le[1]-le_ant[1])/0.05;
			le_dot[2]=(le[2]-le_ant[2])/0.05;
			
			v_le_dot(0) = l_e.getX();  //Representacion en vector3f
			v_le_dot(1)= l_e.getY();
			v_le_dot(2)= l_e.getZ();
			
			//q_e = qConj(q_d)* q_imu; 
			
			//Derivada q_e
			qe_dot[0]=( q_e.getW() - qe_ant[0])/0.5;
			qe_dot[1]=( q_e.getX() - qe_ant[1])/0.5;
			qe_dot[2]=( q_e.getY() - qe_ant[2])/0.5;
			qe_dot[3]=( q_e.getZ() - qe_ant[3])/0.5;
			  
			q_e_dot.setW(qe_dot[0]);
			q_e_dot.setW(qe_dot[1]);
			q_e_dot.setW(qe_dot[2]);
			q_e_dot.setW(qe_dot[3]);
			
			//Error dual debajo de EQ 45
			Theta_e = q2_x(qLn(q_e));    //= 2ln (q_e)  = 2*qLn(qConj(q_d) * q_imu)
			//Verificar como queda dual, y si una parte son ceros debe haber una D_e_q_e w y una v para separar los elementos????
			D_e_q_e_w = q_e * ((Theta_e ) * qConj(q_e));    
			D_e_q_e_v = q_e * ((l_e) * qConj(q_e));
			 
			eqe_w1 = D_e_q_e_w.getW();
			eqe_w2 = D_e_q_e_w.getX();
			eqe_w3 = D_e_q_e_w.getY();
			eqe_w4 = D_e_q_e_w.getZ();
			eqe_v1 = D_e_q_e_v.getW();
			eqe_v2 = D_e_q_e_v.getX(); //x
			eqe_v3 = D_e_q_e_v.getY();
			eqe_v4 = D_e_q_e_v.getZ();
			
			w[0]= veax;
			w[1]= veay;
			w[2]= veaz;
			
			//Es posible pasar w a cuaternion para operar?
			q_w.setX(veax);
			q_w.setY(veay);
			q_w.setZ(veaz);
			
			///EQ 47
			//w_e = q_w +  q2_x(qConj(q_e) )* (qConj(q_d_dot) * q_imu); ////Deseado derivada matematica
			
			w_e = q_w +  q2_x(qConj(q_e) )* (qConj(q_d_dot) * q_imu); ////Deseado
			we[0]= w_e.getX();
			we[1]= w_e.getY();
			we[2]= w_e.getZ();
			
			v_w_e(0)=w_e.getX();   //Representacion en vector3f
			v_w_e(1)=w_e.getY();
			v_w_e(2)=w_e.getZ();
			

			//ve = le_dot + w_e cross le;   ///operacion cross
			//v_ve = v_le_dot + v_w_e.cross(v_le); 
			v_ve = v_le_dot; 
						
			float ve0=0;
			//v_e = Conj(q_imu) * [Dot e_PI - 2*e_PI  cross [q_d * Dot(Conj(q_d))]] * q_imu;
			
			//de donde salen las otras variables   qd y qPId, s son las derivadas numericas?
			q_xi_e_w.setW(w_e.getW());
			q_xi_e_w.setX(w_e.getX());
			q_xi_e_w.setY(w_e.getY());
			q_xi_e_w.setZ(w_e.getZ());
			//q_xi_e_v.setv(ve_w??? - qPId_dot[0]);   ///En esta seccion es cero o uno????
			q_xi_e_v.setW(ve0 );
			q_xi_e_v.setX(v_ve[0] );
			q_xi_e_v.setY(v_ve[1] );
			q_xi_e_v.setZ(v_ve[2] );
				
			D_e_xi_e_w = q_e * (q_xi_e_w * qConj(q_e));  //verificar como queda el dual
			D_e_xi_e_v = q_e * (q_xi_e_v * qConj(q_e));  
			// debe haber una D_e_xi_e w y una v para separar los elementos		
			exie_w1 = D_e_xi_e_w.getW();
			exie_w2 = D_e_xi_e_w.getX();
			exie_w3 = D_e_xi_e_w.getY();
			exie_w4 = D_e_xi_e_w.getZ();
			exie_v1 = D_e_xi_e_v.getW();
			exie_v2 = D_e_xi_e_v.getX();
			exie_v3 = D_e_xi_e_v.getY();
			exie_v4 = D_e_xi_e_v.getZ();
			
			///EQ 76 Superficie
			//	s = Trnsp[sw1 Kw2 sw3] + Trnsp[sv1 sv2 sv3]
			//s =  D_e_q_e + bett1 o Pow(Abs(D_e_q_e),gamm1) o sign(D_e_q_e)+bett2 o Pow(Abs(D_e_xi_e), gamm2) o sign(D_e_xi_e);
			//verificar si quedan lineas las operaciones
			s_w1 = eqe_w1 + bett1_w1 * (pow(abs(eqe_w1),gamm1_w1)) + sgn(eqe_w1) + bett2_w1 * pow(abs(exie_w1),gamm2_w1) * sgn(exie_w1);
			s_w2 = eqe_w2 + bett1_w2 * (pow(abs(eqe_w2),gamm1_w2)) + sgn(eqe_w2) + bett2_w2 * pow(abs(exie_w2),gamm2_w2) * sgn(exie_w2);
			s_w3 = eqe_w3 + bett1_w3 * (pow(abs(eqe_w3),gamm1_w3)) + sgn(eqe_w3) + bett2_w3 * pow(abs(exie_w3),gamm2_w3) * sgn(exie_w3);
			s_w4 = eqe_w4 + bett1_w4 * (pow(abs(eqe_w4),gamm1_w4)) + sgn(eqe_w4) + bett2_w4 * pow(abs(exie_w4),gamm2_w4) * sgn(exie_w4);
			s_v1 = eqe_v1 + bett1_v1 * (pow(abs(eqe_v1),gamm1_v1)) + sgn(eqe_v1) + bett2_v1 * pow(abs(exie_v1),gamm2_v1) * sgn(exie_v1);
			s_v2 = eqe_v2 + bett1_v2 * (pow(abs(eqe_v2),gamm1_v2)) + sgn(eqe_v2) + bett2_v2 * pow(abs(exie_v2),gamm2_v2) * sgn(exie_v2);
			s_v3 = eqe_v3 + bett1_v3 * (pow(abs(eqe_v3),gamm1_v3)) + sgn(eqe_v3) + bett2_v3 * pow(abs(exie_v3),gamm2_v3) * sgn(exie_v3);
			s_v4 = eqe_v4 + bett1_v4 * (pow(abs(eqe_v4),gamm1_v4)) + sgn(eqe_v4) + bett2_v4 * pow(abs(exie_v4),gamm2_v4) * sgn(exie_v4);
			
			// s_w = 
			// s_n = 
			
			///EQ 80 Controlador
			//T_in = Conj(q_e)* {Pow(Abs(D_e_xi_e),2-gamm2) o gamm3 o bett3 o (I_3x3 + bett1 + gamm1 o Pow(Abs(D_e_q_e),gamm1-1)) o Sign(D_e_xi_e) + Pow(Abs(K1),I_3x3) o Pow(Abs(s),K)*sign(s) + Pow(Abs(K2),I_3x3) o s } * q_e;
			//verificar si quedan lineas las operaciones
			p_w1 = pow((abs(exie_w1)),(2-gamm2_w1)) * gamm3_w1 * bett3_w1 * (Iw1 + bett1_w1 + gamm1_w1 * pow((abs(eqe_w1)),(gamm1_w1-1))) * sgn(exie_w1) + pow((abs(K1_w1)),Iw1) * pow((abs(s_w1)),kw1) * sgn(s_w1) + pow((abs(K2_w1)),Iw1) * s_w1;
			p_w2 = pow((abs(exie_w2)),(2-gamm2_w2)) * gamm3_w2 * bett3_w2 * (Iw2 + bett1_w2 + gamm1_w2 * pow((abs(eqe_w2)),(gamm1_w2-1))) * sgn(exie_w2) + pow((abs(K1_w2)),Iw2) * pow((abs(s_w2)),kw2) * sgn(s_w2) + pow((abs(K2_w2)),Iw2) * s_w2;
			p_w3 = pow((abs(exie_w3)),(2-gamm2_w3)) * gamm3_w3 * bett3_w3 * (Iw3 + bett1_w3 + gamm1_w3 * pow((abs(eqe_w3)),(gamm1_w3-1))) * sgn(exie_w3) + pow((abs(K1_w3)),Iw3) * pow((abs(s_w3)),kw3) * sgn(s_w3) + pow((abs(K2_w3)),Iw3) * s_w3;
			p_w4 = pow((abs(exie_w4)),(2-gamm2_w4)) * gamm3_w4 * bett3_w4 * (Iw4 + bett1_w4 + gamm1_w4 * pow((abs(eqe_w4)),(gamm1_w4-1))) * sgn(exie_w4) + pow((abs(K1_w4)),Iw4) * pow((abs(s_w4)),kw4) * sgn(s_w4) + pow((abs(K2_w4)),Iw4) * s_w4;
			p_v1 = pow((abs(exie_v1)),(2-gamm2_v1)) * gamm3_v1 * bett3_v1 * (Iv1 + bett1_v1 + gamm1_v1 * pow((abs(eqe_v1)),(gamm1_v1-1))) * sgn(exie_v1) + pow((abs(K1_v1)),Iv1) * pow((abs(s_v1)),kv1) * sgn(s_v1) + pow((abs(K2_v1)),Iv1) * s_v1;
			p_v2 = pow((abs(exie_v2)),(2-gamm2_v2)) * gamm3_v2 * bett3_v2 * (Iv2 + bett1_v2 + gamm1_v2 * pow((abs(eqe_v2)),(gamm1_v2-1))) * sgn(exie_v2) + pow((abs(K1_v2)),Iv2) * pow((abs(s_v2)),kv2) * sgn(s_v2) + pow((abs(K2_v2)),Iv2) * s_v2;
			p_v3 = pow((abs(exie_v3)),(2-gamm2_v3)) * gamm3_v3 * bett3_v3 * (Iv3 + bett1_v3 + gamm1_v3 * pow((abs(eqe_v3)),(gamm1_v3-1))) * sgn(exie_v3) + pow((abs(K1_v3)),Iv3) * pow((abs(s_v3)),kv3) * sgn(s_v3) + pow((abs(K2_v3)),Iv3) * s_v3;
			p_v4 = pow((abs(exie_v4)),(2-gamm2_v4)) * gamm3_v4 * bett3_v4 * (Iv4 + bett1_v4 + gamm1_v4 * pow((abs(eqe_v4)),(gamm1_v4-1))) * sgn(exie_v4) + pow((abs(K1_v4)),Iv4) * pow((abs(s_v4)),kv4) * sgn(s_v4) + pow((abs(K2_v4)),Iv4) * s_v4;
			
			q_pw.setW(p_w1);
			q_pw.setX(p_w2);
			q_pw.setY(p_w3);
			q_pw.setZ(p_w4);
			q_pv.setW(p_v1);
			q_pv.setX(p_v2);  //x
			q_pv.setY(p_v3);  //y
			q_pv.setZ(p_v4);  //z
				
			
			Tw_in = qConj(q_e)* ( q_pw* q_e);//get  x, y z  son roll, pitch, yaw
			Tv_in = qConj(q_e)* ( q_pv* q_e);  //get  x, y z  son x y z
			
			/// CONTROLADOR PD
			
			pd_w1 = - kp_w1*eqe_w1 - kd_w1*exie_w1;
			pd_w2 = - kp_w2*eqe_w2 - kd_w2*exie_w2;		//roll
			pd_w3 = - kp_w3*eqe_w3 - kd_w3*exie_w3;		//pitch
			pd_w4 = - kp_w4*eqe_w4 - kd_w4*exie_w4;		//yaw
			pd_v1 = - kp_v1*eqe_v1 - kd_v1*exie_v1;			
			pd_v2 = - kp_v2*eqe_v2 - kd_v2*exie_v2;			//x
			pd_v3 = - kp_v3*eqe_v3 - kd_v3*exie_v3;			//y
			pd_v4 = - kp_v4*eqe_v4 - kd_v4*exie_v4;			//z
			
			//***** Control de Yaw
			eyaw=posyaw-yawDes;  					//Error yaw
			eyaw_p=(eyaw-eyaw_ant)/0.05;		//Derivada de error yaw
				
			/// Controlador PID
			yyaw=kpyaw*eyaw+kdyaw*eyaw_p;		//PID			


			//X //control
			ctrl_x=-Tv_in.getX();
			//ctrl_x = pd_v2;										
			ux=offset(ctrl_x);							
			usx=satura(ux);								
			usx=1500; 								
			
			//Y
			ctrl_y =Tv_in.getY();
			//ctrl_y = pd_v3;										
			uy=offset(ctrl_y);					
			usy=satura(uy);					
			//usy=1500; 							
			
			//Z
			ctrl_z = pd_v4;							
			uz=offset(ctrl_z);		
			usz=satura(uz);					
			usz=1500; 							
			
			//Roll
			ctrl_roll = pd_w2;					
			uroll=offset(ctrl_roll);			
			usroll=satura(uroll);			
			usroll=1500;  					
				
			//Pitch
			ctrl_pitch=pd_w3;
			upitch=offset(ctrl_pitch);		
			uspitch=satura(upitch);		
			uspitch=1500;  					
			
			//Yaw   1530  1475  -- limites movimiento
			//ctrl_yaw=-pd_w4;   			//	PD  Señal negativa cuando quiere girar a la derecha video de atras.
			//ctrl_yaw=Tw_in.getZ();   			//	SMC  
			ctrl_yaw=yyaw;
			uyaw=offset(ctrl_yaw);								
			usyaw=satura(uyaw);			
			usyaw=1500;  								
			
			verticalc.data=usz;	
			fforwardc.data=usx; 
			lateralc.data=usy; 
			rollc.data=usroll; 
			pitchc.data=uspitch;
			yawc.data=usyaw;
			
		
			// Guarda variables en txt
			myfile<< std::setprecision(4) <<tiempo<<"\t" <<q_PId.getW()<<"\t" <<q_PId.getX()<<"\t" <<q_PId.getY()<<"\t" <<q_PId.getZ() << "\t"<<q_imu.getW()<< "\t"<<q_imu.getX()<< "\t"<<q_imu.getY()<< "\t"<<q_imu.getZ()<< "\t"<<pd_w1<< "\t"<<pd_w2<< "\t"<<pd_w3<< "\t"<<pd_w4<< "\t"<<pd_v1<< "\t"<<pd_v2<< "\t"<<pd_v3<< "\t"<<pd_v4<< "\t"<<usx<< "\t"<<usy<< "\t"<<usz<< "\t"<<usroll<< "\t"<<uspitch<< "\t"<<usyaw<< "\t"<<(poszedx-offsetx)*4<< "\t"<<(poszedy-offsety)*4<< "\t"<<poszedz<< "\t"<< l_e.getX()<< "\t"<<l_e.getY()<<"\t"<<q_e.getW()<<"\t"<<q_e.getX()<<"\t"<<q_e.getY()<<"\t"<<q_e.getZ()<<"\t"<< D_e_q_e_v.getX()<< "\t"<< D_e_q_e_v.getY()<<"\n";
				


				//################# FINALIZA EL CONTROLADOR ################# 

				// publica señal de controlador
				pubVertical.publish(verticalc);
				pubForward.publish(fforwardc);
				pubLateral.publish(lateralc);
				pubRoll.publish(rollc);
				pubPitch.publish(pitchc);
				pubYaw.publish(yawc);
				
			  
			    //////////////////// GUARDA VARIABLES ANTERIORES ////////////////
			    ex_ant = ex;
			    ey_ant = ey;
			    ez_ant = ez;
			    eyaw_ant = eyaw;		
				eroll_ant = eroll;		
				epitch_ant = epitch;	
				
				le_ant[0]= l_e.getX();
				le_ant[1]= l_e.getY();
				le_ant[2]= l_e.getZ();
				
				qe_ant[0]= q_e.getW();
				qe_ant[1]= q_e.getX();
				qe_ant[2]= q_e.getY();
				qe_ant[3]= q_e.getZ();
				
				qd_ant[0] = q_d.getW();
				qd_ant[1] = q_d.getX();
				qd_ant[2] = q_d.getY();
				qd_ant[3] = q_d.getZ();
		
				qPId_ant[0] = q_PId.getW();
				qPId_ant[1] = q_PId.getX();
				qPId_ant[2] = q_PId.getY();
				qPId_ant[3] = q_PId.getW();
			    
				//#################################################################################//
				//VARIABLES A GUARDAR EN ARCHIVO TXT

printf("t= %0.3f - x= %0.3f - y= %0.3f - le_x= %0.3f - qe_x= %0.3f - us_x= %d - us_y= %d - qimu_w= %0.3f - qimu_x= %0.3f - qimu_y= %0.3f - qimu_z= %0.3f - eqe_x= %0.3f\n",tiempo ,(poszedx-offsetx)*4,(poszedy-offsety)*4, l_e.getX(), q_e.getX(), usx, usy, q_imu.getW(), q_imu.getX(), q_imu.getY(), q_imu.getZ(), D_e_q_e_v.getX());



				r=r+1;  //iterador ref tray z
				t=t+1;  //iterador del ciclo principal
		}
		if(tiempo>t_eje)
		{
			controles=false;
			printf("Finaliza control\n");
			//usz2=1500;
		}
		
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
		
	}
	
	if(controles == false) 
	{ 
	printf("pos_y= %0.3f - pos_y= %0.3f - qimu_w= %0.3f - qimu_x= %0.3f - qimu_y= %0.3f - qimu_z= %0.3f \n", (poszedx-offsetx)*2,(poszedy-offsety)*4, q_imu.getW(), q_imu.getX(), q_imu.getY(), q_imu.getZ());

	//printf("uyaw= %d \t yaw= %0.3f \n",axis_yaw , posyaw);
	}
		

	
	
	ros::spinOnce();
	loop_rate.sleep();
  }
  delete H;
  myfile.close();
  return 0;
}

//Funcion de saturacion de señal hacia propulsores 
float satura(float a)
{
  if (a >1650)
  {
     a = 1650;
	 return a;
  }
  else if (a < 1350)
  {    
	 a = 1350;
     return a;
  }
  return a;
}


//saturacion offset de los motores 1530  1475  -- limites movimiento
float offset(float d)
{
  float out;
  if(d >= 0)
  {
     out = (1530+d); //1518
	 return out;
  }
  else if(d  < 0)
  {    
	 out = (1475+d); //1482
     return out;
  }
}




//Fcn Signo
int sgn(float in)
{
  int s;
	
  if (in > 0)
  {
     s = 1;
	 return s;
  }
  else if (in < 0)
  {    
	 s = -1;
     return s;
  }
  return s;
	
}

//Funcion Normalizacion
tf2::Quaternion qNorm(tf2::Quaternion q_in4)
{
	tf2::Quaternion q_out4;
	double norm2=0, rw2=0, rx2=0, ry2=0, r2=0;
	
	///Normalizacion de cuaternion
	norm2=sqrt( pow(q_in4.getW(),2) + pow(q_in4.getX(),2) + pow(q_in4.getY(),2) + pow(q_in4.getZ(),2));
		
	if (norm2 == 0)
	{
		q_out4.setW (0);
		q_out4.setX (0);
		q_out4.setY (0);
		q_out4.setZ (0);
		return q_out4;
	}
	else 
	{
		q_out4.setW ((q_in4.getW() / norm2 ));
		q_out4.setX ((q_in4.getX() / norm2 ));
		q_out4.setY ((q_in4.getY() / norm2 ));
		q_out4.setZ ((q_in4.getZ() / norm2 ));
		return q_out4;
	}
		
	return q_out4;
}

//Funcion conjugado 
tf2::Quaternion qConj(tf2::Quaternion q_in)
{
	tf2::Quaternion q_out;
	
	q_out.setW (q_in.getW());
	q_out.setX (-q_in.getX());
	q_out.setY (-q_in.getY());
	q_out.setZ (-q_in.getZ());
	
	return q_out;
}

//Funcion qLn
tf2::Quaternion qLn(tf2::Quaternion q_in2)
{
	tf2::Quaternion q_out2;
	
	double norm=0, rw=0, rx=0, ry=0, r=0;
	q_in2 = qNorm(q_in2);
	
	///Normalizacion de cuaternion
	
	
	norm=sqrt( pow(q_in2.getW(),2) + pow(q_in2.getX(),2) + pow(q_in2.getY(),2) + pow(q_in2.getZ(),2));
		
	if (norm == 0)
	{
		q_out2.setW (0);
		q_out2.setX (0);
		q_out2.setY (0);
		q_out2.setZ (0);
		return q_out2;
	}
	else 
	{
		q_out2.setW ((q_in2.getW() / norm ) * acos(q_in2.getW()));
		q_out2.setX ((q_in2.getX() / norm ) * acos(q_in2.getW()));
		q_out2.setY ((q_in2.getY() / norm ) * acos(q_in2.getW()));
		q_out2.setZ ((q_in2.getZ() / norm ) * acos(q_in2.getW()));
		return q_out2;
	}
		
	return q_out2;
}

//Funcion conjugado 
tf2::Quaternion q2_x(tf2::Quaternion q_in3)
{
	tf2::Quaternion q_out3;
	
	q_out3.setW (2*q_in3.getW());
	q_out3.setX (2*q_in3.getX());
	q_out3.setY (2*q_in3.getY());
	q_out3.setZ (2*q_in3.getZ());
	
	return q_out3;
}
