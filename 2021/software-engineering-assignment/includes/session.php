<?php
include('config.php');
session_start();

if (isset($_SESSION['user'])) {
   $user_name = $_SESSION['user'];
   $ses_sql = mysqli_query($db, "SELECT user_id, user_role FROM user WHERE user_name = '$user_name'");
   $row = mysqli_fetch_array($ses_sql, MYSQLI_ASSOC);
   $user_id = $row['user_id'];
   $user_role = $row['user_role'];
}
