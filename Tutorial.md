## **Tutorial**
#### SoftwareSerial
```bash
ArduinoCoding:    #include <SoftwareSerial.h> //gia lap TX RX 
                               SoftwareSerial mySerial(9, 10); 
Chức năng: Có thể tham khảo trên internet, nhưng hiểu một cách nôm na là như sau
          Mọi tín hiệu truyền nhận đều được gửi qua dưới dạng TX, RX (truyền đi và nhận về). Trên arduino cũng có 2 chân tx, rx này (chính là chân số 0 và 1), nhưng không được dùng nó cho việc truyền nhận tin nhắn của module, bởi lẽ 2 chân này nó sẽ làm nhiệm vụ truyền nhận tín hiệu giữa arduino và máy tính (phải có 2 chân này mới có thể nạp chương trình, giao tiếp với máy tính được), do đó ta phải sử dụng 2 chân khác của arduino. Ta thực hiện câu lệnh trên để giả lập các chân bất kì của arduino trở thành chức năng của TX, RX cho module sim thay vì chức năng digital, analog của nó vốn có ban đầu.
```
#### GSM_in_ArduinoCoding_with_AT_Command (một số tập lệnh AT cơ bản dùng trong GSM tin nhắn)
```bash
1.	Code to Send the Message
                AT+CMGF=[mode]<CR><LF>
               Chức năng: Thiết lập định dạng đọc ghi của tin nhắn.
               Mode = 1: Text mode (chức năng gửi tin nhắn hiển thị dạng text bình thường)
               Mode = 2: PDU mode (chức năng gửi và hiển thị theo kiểu binary information 7 bit hoặc 8 bit) 
	Setup for ArduinoCoding: mySerial.println("AT+CMGF=1");
AT+CMGS=[phoneNumber]<CR><LF>
Chức năng: Thực hiện gửi tin nhắn vào phone Number
	Setup for ArduinoCoding: mySerial.println("AT+CMGS=\"+84834234523\"\r");

	Bắt đầu soạn tin nhắn và gửi: 

   mySerial.println("Nội dung tin nhắn muốn gửi");
   delay(100); 
   mySerial.println((char)26);// chuyển chế độ ASCII 
   delay(1000);
               Note: Cũng giống như con người, không thể một lúc thực hiện nhiều công việc, do đó khoảng giữa ở các tập lệnh phải có delay, để nó có thời gian chờ để thực hiện tuần tự các lệnh ở mức ổn định (không thể một lúc thực hiện nhiều lệnh truyền nhận vậy được => sẽ bị treo, nhiễu thông tin,..).
2.	Code to Receive the Message
   AT+CNMI=[mode]<CR><LF>
Chức năng: Thiết lập kiểu xử lý tin nhắn
Mode = 2,1,0,0 : mode hiển thị vị trí tin nhắn+CMTI
Mode = 2,2,0,0 : mode hiển thị nội dung tin nhắn+CMT
	Setup for ArduinoCoding: mySerial.println("AT+CNMI=2,2,0,0"); 

3.	Code to Make call
   ATD[PhoneNumber];<CR><LF>
Chức năng: Thực hiện cuộc gọi, module sẽ trả về với các đáp ứng sau
                            + Cuộc gọi bị mất sóng: NO DIALTONE
                            + Cuộc gọi bị ngắt: BUSY
                              + Cuộc gọi đã kết thúc: NO CARRIER
                              + Cuộc gọi không nhận được trả lời: NO ANSWER
	Setup for ArduinoCoding: mySerial.println("ATD+84834234523;");

4.	Code to HangupCall
    ATD<CR><LF>
    Chức năng: Kết thúc cuộc gọi hoặc ngắt máy khi có cuộc gọi đến
	Setup for ArduinoCoding: mySerial.println("ATH");	

5.	Code to ReceiveCall
  ATA<CR><LF>
Chức năng: Chấp nhận cuộc gọi đến
	Setup for ArduinoCoding: mySerial.println("ATA");

```
Nguồn tham khảo tập lệnh AT đầy đủ: https://tapit.vn/huong-dan-su-dung-mot-chuc-nang-cua-module-sim900a/ 
