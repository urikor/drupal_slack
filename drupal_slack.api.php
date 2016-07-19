<?php
/**
 * @file
 * API documentation for Drupal Slack.
 */

/**
 * Passes array with text for finding in Slack messages and replacing
 * with link.
 * Each element contains text to find and link address.
 * @return mixed
 */
function hook_slack_message_links() {
  $links = array(
    array(
      'text' => 'Slack',
      'link' => 'https://api.slack.com',
    ),
    array(
      'text' => 'Drupal',
      'link' => 'http://drupal.org',
    ),
  );

  return $links;
}
