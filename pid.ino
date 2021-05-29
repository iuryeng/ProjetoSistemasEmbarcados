
#define sensor         A0
#define controle       3


double kP, kI, kD;      
double P, I, D;
double pid;
double error;
double valorLido;
double ultimoValorLido;
	
double setPoint;
long lastProcess;	



void setup() {
	Serial.begin(9600);	
	pinMode(sensor, INPUT);
	pinMode(controle, OUTPUT);
}

int controlePwm = 50;

void loop() {

// Implementação PID
		error = setPoint - valor;
		float intervaloTempo = (millis() - lastProcess) / 1000.0;
		lastProcess = millis();		
		
		P = error * kP;			
		I = I + (error * kI) * intervaloTempo;		
		D = (ultimoValorLido - valor) * kD / intervaloTempo;
		ultimoValorLido = valor;
		

		pid = P + I + D;

	double temperature = map(analogRead(sensor), 0, 1023, 0, 100);
	
	controlePwm = pid + 50);
	analogWrite(controle, controlePwm);
	
}