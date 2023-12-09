# --------------------------------------------------------------
# Warning-system-of-traffic-lights-and-blind-spots-at-intersections
# hệ thống cảnh báo đèn giao thông và điểm mù tại các giao lộ


# --------------------------------------------------------------


## thu tín hiệu khi sắp có đèn đỏ, có xe từ hướng khác đến giao lộ.
## phát tín hiệu khi đến giao lộ. Mã phát ra là biển số xe.
# --------------------------------------------------------------
## //xe (unoR3)
const int IR_RECEIVE_PIN = 2;    // Pin used to connect the IR receiver module (IR1838)
const int IR_TRANSMIT_PIN = 10;   // Pin used to connect the IR LED for transmission
const int coi =9;
const int denXanh=4;
const int denDo=5;
const int denVang=6;
# --------------------------------------------------------------
## //den (mega2560)
đèn đỏ 144444 244444 //mã output
có xe 122222 222222 //mã output

denXanh1=6;
denVang1=7;
denDo1=8;

denXanh2=9;
denVang2=10;
denDo2=11;

timeXanh1=10000/2;   //1s=1000mls 
timeXanh2=10000/2;
timeVang=3000/2;
# --------------------------------------------------------------
