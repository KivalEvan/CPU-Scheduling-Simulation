<?php
require_once(__DIR__ . "/../includes/constants.php");
include(__DIR__ . "/../includes/session.php");

if (isset($_SESSION["user"])) {
    header("location: " . ROOT_SITE);
}

$username = $password = "";
$username_err = $password_err = $login_err = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (empty(trim($_POST["username"]))) {
        $username_err = "Please enter username.";
    }
    if (empty(trim($_POST["password"]))) {
        $password_err = "Please enter your password.";
    }

    if (empty($username_err) && empty($password_err)) {
        $username = mysqli_real_escape_string($db, $_POST['username']);
        $password = mysqli_real_escape_string($db, $_POST['password']);

        $query = "SELECT user_id FROM user WHERE user_name = '$username' and user_password = '$password'";
        $result = mysqli_query($db, $query) or die(mysqli_error($db));
        $row = mysqli_fetch_array($result, MYSQLI_ASSOC);

        $count = mysqli_num_rows($result);

        if ($count == 1) {
            session_start();
            $_SESSION['user'] = $username;
            header("location: " . ROOT_SITE);
        } else {
            $login_err = "Invalid username or password.";
        }
    }
}

?>
<!DOCTYPE html>
<html>

<head>
    <title>Online Objective Exam</title>
    <link rel="stylesheet" href="<?php echo ROOT_SITE ?>/assets/style.css">
</head>

<body>
    <?php $result ?>
    <?php include_once(ROOT_PATH . '/includes/header.php') ?>
    <main class="wrapper">
        <div class="login">
            <div class="login-header">
                <div class="login-profile">
                    <img src="<?php echo ROOT_SITE ?>/assets/pfp-blank.webp">
                </div>
            </div>
            <form action="" method="post">
                <input type="text" name="username" placeholder="User_ID123" value=<?php echo $username ?>><br>
                <input type="password" name="password" placeholder="Password"><br>
                <br>
                <input type="submit" value="Login"><br>
                <?php if ($username_err != "") : ?>
                    <span class="login-error"><?php echo $username_err ?></span><br>
                <?php endif ?>
                <?php if ($password_err != "") : ?>
                    <span class="login-error"><?php echo $password_err ?></span><br>
                <?php endif ?>
                <?php if ($login_err != "") : ?>
                    <span class="login-error"><?php echo $login_err ?></span><br>
                <?php endif ?>
                <div class="register-login">
                    <span>No account? <a href="../register/">Register here.</a></span>
                </div>
                <br>
            </form>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>