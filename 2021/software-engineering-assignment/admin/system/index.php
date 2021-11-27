<?php
require_once(__DIR__ . "/../../includes/constants.php");
include(__DIR__ . "/../../includes/session.php");
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
                <div class="content-header">
                    Current Server Access: Open
                </div>
                <br>
                <div class="content-header">
                    Current Online Users: -
                </div>
                <br>
                <div class="content-element">
                    Restrict Server Access
                </div>
                <div class="content-element">
                    <div>
                        Install New Update
                    </div>
                    <div>
                        Install New Patch
                    </div>
                </div>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>