<?php
require_once(__DIR__ . '/includes/constants.php');
include(__DIR__ . '/includes/session.php');
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
        <?php include_once(ROOT_PATH . '/includes/navigation.php') ?>
        <div class="content">
            <div class="content-wrapper">
                <?php if (isset($_SESSION['user'])) : ?>
                    <h2>Welcome to online objective exam dashboard.</h2>
                <?php else : ?>
                    <h2>You are not logged in.</h2>
                <?php endif ?>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>