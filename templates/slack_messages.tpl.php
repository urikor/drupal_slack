<div>
  <?php if (is_array($messages)) : ?>
    <?php foreach($messages as $msg) : ?>
      <div class="item"><?php print render($msg); ?></div>
    <?php endforeach; ?>
  <?php else : ?>
    <?php print render($messages); ?>
  <?php endif; ?>
</div>
