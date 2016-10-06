#include "hwlib.hpp"

class IRRecieve{
private:
	int const active = 100'000;
	long int last_signal = hwlib::now_us() - active;
	hwlib::target::pin_in data;
	hwlib::target::pin_out showPin;
public:
	IRRecieve(hwlib::target::pin_in & data, hwlib::target::pin_out & showPin):
		data(data),
		showPin(showPin)
	{}
   
	void getSignal(){
		int numberOfRecievedBits = 0;
		int bitPaternRecieved[15];
		int savedBitPaternRecieved[15];
		
		
		for(;;){
			
			if( ( (last_signal + active ) > hwlib::now_us() ) && numberOfRecievedBits < 15){
				showPin.set(1);
				bitPaternRecieved[numberOfRecievedBits] = 1;
				numberOfRecievedBits++;
			}
			else if( ( (last_signal + active ) < hwlib::now_us() ) && numberOfRecievedBits < 15){
				showPin.set(0);
				bitPaternRecieved[numberOfRecievedBits] = 0;
				numberOfRecievedBits++;
			}
			else if(numberOfRecievedBits == 15){
				for(int i = 0; i < 15; i++){
					if(bitPaternRecieved[i] != savedBitPaternRecieved[i]){
						for(int j = 0; j < 15; j++){
							hwlib::cout << bitPaternRecieved[j];
							savedBitPaternRecieved[j] = bitPaternRecieved[j];
						}
						hwlib::cout << "\n";
					}
				}
				numberOfRecievedBits = 0;
				showPin.set(0);
			}
				
			if( data.get() == 0 ){
				last_signal = hwlib::now_us();
			}
		}
	}
	
	
};