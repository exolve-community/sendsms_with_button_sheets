function sendSMSFromCell() {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
  var messageCell = sheet.getRange('A1');  // Ячейка для сообщения
  var destinationCell = sheet.getRange('B1');  // Ячейка для номера получателя
  var smsContent = messageCell.getValue();
  var phoneNumber = destinationCell.getValue();

  // Проверка на пустые значения
  if (!smsContent || !phoneNumber) {
    Logger.log('Message or phone number is empty');
    return;
  }

  // Убедитесь, что номер телефона и текст сообщения передаются как строки
  sendSMS('номер из exolve', String(phoneNumber), String(smsContent)); // Номер отправителя, номер получателя, текст сообщения
}

function sendSMS(number, destination, text) {
  var apiUrl = 'https://api.exolve.ru/messaging/v1/SendSMS';
  
  var payload = {
    'number': number,       // Номер отправителя
    'destination': destination, // Номер получателя
    'text': text           // Текст сообщения
  };
  
  Logger.log('Payload: ' + JSON.stringify(payload));
  
  var options = {
    'method': 'post',
    'contentType': 'application/json',
    'headers': {
      'Authorization': 'Bearer [ваш токен]' // Замените на ваш токен
    },
    'payload': JSON.stringify(payload),
    'muteHttpExceptions': true  // Чтобы увидеть полный ответ при ошибке
  };
  
  try {
    var response = UrlFetchApp.fetch(apiUrl, options);
    Logger.log('Response code: ' + response.getResponseCode());
    Logger.log('Response body: ' + response.getContentText());
  } catch (error) {
    Logger.log('Error: ' + error.toString());
  }
}

function testSendSMS() {
  sendSMSFromCell();
}
