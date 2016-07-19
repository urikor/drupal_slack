<?php
/**
 * Gets messages from remote Slack service.
 * @return mixed
 */
function ds_get_messages() {
  $domain = variable_get('ds_domain');
  $channel = variable_get('ds_channel');
  $token = variable_get('ds_token');
  $msg_number = variable_get('ds_msg_number', 3);

  $query_string = $domain . "/api/channels.history?token=" . $token . "&channel=" . $channel . "&count=" . $msg_number;

  $out = '';
  if ($domain && $channel && $token) {
    $response = file_get_contents($query_string);
    if (!empty($response)) {
      $response = json_decode($response);

      if (!empty($response->messages)) {
        foreach ($response->messages as $msg) {
          $text = $msg->text;
          $text_links = module_invoke_all('slack_message_links');
          if (!empty($text_links)) {
            $text = ds_add_links($msg->text, $text_links);
          }
          $out[] = $msg->user . ': ' . $text;
        }
      } else {
        $out = t('No messages');
      }
    } else {
      $out = t("Slack service does not respond.");
    }
  } else {
    global $user;
    $settings_link = '';
    if (in_array('administrator', $user->roles)) {
      $settings_link = l('admin/config/drupal_slack', 'admin/config/drupal_slack');
    }
    $out = t("Wrong Slack settings.") . $settings_link;
  }

  return theme('slack_messages', array('messages' => $out));
}

/**
 * Add links to particular text.
 * @param string $text
 * @param mixed $text_links
 * @return mixed
 */
function ds_add_links($text, $text_links) {
  if (!empty($text_links)) {
    foreach ($text_links as $text_link) {
      $text = str_replace($text_link['text'], '<a href="' . $text_link['link'] . '">' . $text_link['text'] . '</a>', $text);
    }
  }

  return $text;
}
