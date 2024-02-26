# connected_embedded_systems

Set of classes to interface to a DS3231 I2C Device.

To compile the code:
```bash
g++ Application.cpp RealTimeClock.cpp I2CDevice.cpp DateTimeParser.cpp -o rtc
```

To set the time:
```bash
./rtc set-time 'Day dd/mm/yyyy hh:mm:ss'
```
e.g. `./rtc set-time 'Monday 26/02/2024 14:44:23'`

Setting an alarm:
```bash
./rtc set-alarm [dy|dt] 'dd hh:mm:ss' [1|2]
```
e.g. `./rtc set-alarm dt '19 21:58:30' 1`

Output square wave:
```bash
./rtc start-sqw [1|2|3|4]
```

Stop square wave:
```bash
./rtc stop-sqw
```