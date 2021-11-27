<?php
require_once(__DIR__ . '/../includes/constants.php');
session_start();

if (session_destroy()) {
    header("Location: " . ROOT_SITE);
}
exit;
