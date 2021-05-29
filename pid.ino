

class PID{
public:
	
	double error; //erro para realimentacao do sistema
	double valorLido; //amostra atual
	double ultimoValorLido; //amostra anterior
	double kP, kI, kD;       //parametros do sistema de controle com realimentacao
	double P, I, D;
	double pid;
	
	double setPoint;
	long lastProcess;

	PID(double _kP, double _kI, double _kD){
		kP = _kP;
		kI = _kI;
		kD = _kD;
	}
	
	void addNewvalorLido(double _valorLido){
		valorLido = _valorLido;
	}
	
	void setSetPoint(double _setPoint){
		setPoint = _setPoint;
	}
	
	double process(){
		// Implementação PID
		error = setPoint - valorLido;
		float deltaTime = (millis() - lastProcess) / 1000.0;
		lastProcess = millis();
		
		//P
		P = error * kP;
		
		//I
		I = I + (error * kI) * deltaTime;
		
		//D
		D = (ultimoValorLido - valorLido) * kD / deltaTime;
		ultimoValorLido = valorLido;
		
		// total
		pid = P + I + D;
		
		return pid;
	}
};

#define sensor         A0
#define controle       3

PID PID(1.0, 0, 0);

void setup() {
	Serial.begin(9600);
	PID.setSetpoint(230.0);
	pinMode(sensor, INPUT);
	pinMode(controle, OUTPUT);
}

int controlePwm = 50;

void loop() {
	
	// Lê temperatura
	double temperature = map(analogRead(sensor), 0, 1023, 0, 250);
	
	// Manda pro objeto PID!
	PID.addNewvalorLido(temperature);
	
	
	// Converte para controle
	controlePwm = (PID.process() + 50);
	// Saída do controle
	analogWrite(controle, controlePwm);
	
}
