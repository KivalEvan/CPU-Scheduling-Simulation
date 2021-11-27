<?php
require_once(__DIR__ . "/../includes/constants.php");
include(__DIR__ . "/../includes/session.php");

if (isset($_SESSION["user"])) {
    header("location: " . ROOT_SITE);
}

$username = "";
$email    = "";
$errors = array();

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $username = mysqli_real_escape_string($db, $_POST['username']);
    $password_1 = mysqli_real_escape_string($db, $_POST['password']);
    $password_2 = mysqli_real_escape_string($db, $_POST['cpassword']);
    $email = mysqli_real_escape_string($db, $_POST['email']);
    $fname = mysqli_real_escape_string($db, $_POST['fname']);
    $lname = mysqli_real_escape_string($db, $_POST['lname']);
    $phone = mysqli_real_escape_string($db, $_POST['phone']);

    if (empty($username)) {
        array_push($errors, "Username is required");
    }
    if (empty($password_1)) {
        array_push($errors, "Password is required");
    }
    if ($password_1 != $password_2) {
        array_push($errors, "The two passwords do not match");
    }
    if (empty($email)) {
        array_push($errors, "Email is required");
    }
    if (empty($fname) || empty($lname)) {
        array_push($errors, "Name is required");
    }
    if (empty($phone)) {
        array_push($errors, "Phone is required");
    }

    $query = "SELECT * FROM user WHERE user_name='$username' OR user_email='$email' LIMIT 1";
    $result = mysqli_query($db, $query);
    $user = null;
    if ($result) {
        $user = mysqli_fetch_array($result, MYSQLI_ASSOC);
    }

    if ($user) { // if user exists
        if ($user['username'] === $username) {
            array_push($errors, "Username already exists");
        }

        if ($user['email'] === $email) {
            array_push($errors, "Email already exists");
        }
    }

    if (count($errors) == 0) {
        $query = "INSERT INTO user (user_name, user_password, user_email, user_fname, user_lname, user_phone) 
                  VALUES('$username', '$password_1', '$email', '$fname', '$lname', '$phone')";
        mysqli_query($db, $query);
        header('location: ' . ROOT_SITE . '/login/');
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
    <?php include_once(ROOT_PATH . '/includes/header.php') ?>
    <main class="wrapper">
        <div class="login register">
            <div class="login-header">
                <div class="register-profile">
                    <img src="<?php echo ROOT_SITE ?>/assets/pfp-blank.webp">
                </div>
            </div>
            <form action="" method="post">
                <label for="username">Username: </label>
                <input type="text" id="username" name="username" placeholder="User_ID123"><br>
                <label for="password">Password: </label>
                <input type="password" id="password" name="password" placeholder="Password"><br>
                <label for="cpassword">Confirm Password: </label>
                <input type="password" id="cpassword" name="cpassword" placeholder="Password"><br>
                <label for="email">Email: </label>
                <input type="text" id="email" name="email" placeholder="example@mail.com"><br>
                <label for="fname">First Name: </label>
                <input type="text" id="fname" name="fname" placeholder="First Name"><br>
                <label for="lname">Last Name: </label>
                <input type="text" id="lname" name="lname" placeholder="Last Name"><br>
                <label for="phone">Phone: </label>
                <input type="phone" id="phone" name="phone" placeholder="012-3456789"><br>
                <br>
                <br>
                <input type="submit" value="Register"><br>
                <?php if (count($errors) > 0) : ?>
                    <?php foreach ($errors as $error) : ?>
                        <span class="login-error"><?php echo $error ?></span><br>
                    <?php endforeach ?>
                <?php endif ?>
                <div class="register-login">
                    <span>Already have an account? <a href="../login/">Login here.</a></span>
                </div>
                <br>
            </form>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>