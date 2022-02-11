## **Thứ tự test các file**
#### 1. GSM_with_arduino
```bash
File này test tính hoạt động của module sim 800A, test khả năng gửi, nhận tin nhắn, khả năng gọi điện đến sim khác.
```
#### 2. Combine_between_GSM_and_SR04
```bash
-	File này kết hợp module sim 800A và một sensor
-	Lấy ví dụ cảm biến khoảng cách SR04 (có thể thay bằng các cảm biến tương tự khác). Nếu tín hiệu ở sensor thay đổi, module sim sẽ trả về tin nhắn hoặc gọi điện.
-	Cụ thể test code: nếu khoảng cách SR04 <15cm, thì module tự động gọi hoặc gửi tin nhắn về cho số máy khác.
```
#### 3. GPS_with_LON_LAT
```bash
-	Code test đọc toạ độ thuần từ module GPS và arduino
-	Kết nối thiết bị, chờ đền gps nhấp nháy liến tục thì lúc đã gps đã bắt đc sóng.
-	Nạp code => hiển thị kết quá
```
#### 4. ControlDeviceMessageTest_800A
```bash
-	File này để test khả năng điều khiển thiết bị bằng cách gọi điện thông qua module sim 800A, cụ thể điều khiển led1 ở chân số 12 arduino.
-	Một số lưu í về code: 
+ mySerial.find("#A."): hàm tìm kí tự trả về giá trị 0,1.
+ mySerial.read(): đọc từng kĩ tự được truyền vào cổng serial.
+ strncmp (str1, str2, size): hàm so sánh 2 chuỗi trong đó size là số ký tự tối đa để so sánh:
                                                    Hàm trả về giá trị là:  <0 nếu str1 ngắn hơn str2
                                                                             >0 nếu str1 dài hơn str2
                                                                             =0 nếu str1 = str2
```
#### 5. FeedbackTheMessage
```bash
-	Use the library: TinyGPS++ (Plus).
-	In TinyGPS++ library:
+ Serial.println(gps.location.lat(), 6);    // lấy kinh độ, mặc định setup là 6, theo như tìm hiểu ở code thì 6 này có thể là phần chữ số thập phân được lấy, nếu muốn chắc chắn => check code trong library sẽ rõ.
+ dtostrf(gps.location.lat(),2,6,Templat);      //Get lat from tinyGPS++ and convert to string with 5 decimal places (6 chữ số thập phân đàng sau, rồi lưu vào biến Templat)
+ mySerial.listen():  Enalbe the selected software serial port to listen. Just only one port can listen at a time. Data that arrives for other ports will be discarded. Return: boolean – return true if it replaces another.
+  //Nạp liên tục kí tự vào gps từ vệ tinh
           while (ss.available() > 0)
           gps.encode(ss.read());
   //Truy suất thông tin muốn lấy
           if (gps.altitude.isUpdated())
          Serial.println(gps.altitude.meters());  //lấy chiều cao vị trị.                                        =0 nếu str1 = str2
```
