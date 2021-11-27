<?php
require_once('constants.php');
?>

<header>
    <div>
        <div class="header-profile">
            <?php if (isset($_SESSION['user'])) : ?>
                <a href="<?php echo ROOT_SITE ?>/profile/"><?php echo $_SESSION['user'] . ' (' . ucfirst($user_role) . ')' ?></a><img src="<?php echo ROOT_SITE ?>/assets/pfp-blank.webp">
            <?php endif ?>
        </div>
        <h1><a href=<?php echo ROOT_SITE ?>>Online Objective Exam</a></h1>
    </div>
    <div>
        <span>Current time: <time id="time"><?php echo date('H:i:s d-m-Y') ?></time></span>
        <script>
            startTime();

            function startTime() {
                const today = new Date();
                let h = today.getHours();
                let m = today.getMinutes();
                let s = today.getSeconds();
                let d = today.getUTCDate();
                let M = today.getMonth();
                let y = today.getFullYear();
                m = checkTime(m);
                s = checkTime(s);
                document.getElementById('time').innerHTML = `${h}:${m}:${s} ${d}-${M+1}-${y}`;
                setTimeout(startTime, 1000);
            }

            function checkTime(i) {
                if (i < 10) {
                    i = "0" + i
                };
                return i;
            }
        </script>
    </div>
</header>