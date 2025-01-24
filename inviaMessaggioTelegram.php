<?php
function inviaMessaggioTelegram($id, $msg, $token = '', $silent = false) {
    $data = array(
        'chat_id' => $id,
        'text' => $msg,
        'parse_mode' => 'html',
        'disable_web_page_preview' => true,
        'disable_notification' => $silent
    );
    if($token != '') {
      $ch = curl_init('https://api.telegram.org/bot'.$token.'/sendMessage');
      curl_setopt_array($ch, array(
          CURLOPT_HEADER => 0,
          CURLOPT_RETURNTRANSFER => 1,
          CURLOPT_POST => 1,
          CURLOPT_POSTFIELDS => $data
      ));
      curl_exec($ch);
      curl_close($ch);
    }
}
?>

/*
    esempio uso:
    inviaMessaggioTelegram(	"id_destinatario",
							"messaggio di testo",
							"token HTTP API",
							false);
*/
