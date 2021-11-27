<?php
$path = 'path';
define('ROOT_PATH', str_replace('\includes', '', __DIR__));
define('ROOT_SITE', str_replace([$_SERVER['DOCUMENT_ROOT'], 'index.php'], '', str_replace('\\', '/', ROOT_PATH)));
