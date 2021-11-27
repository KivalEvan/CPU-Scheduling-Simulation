<?php
require_once('constants.php');
?>

<nav>
    <ul>
        <?php if (isset($_SESSION["user"])) : ?>
            <?php if ($user_role === 'admin') : ?>
                <li>
                    <a href="/..<?php echo ROOT_SITE ?>/admin/">Admin</a>
                    <ul>
                        <li>
                            <a href="/..<?php echo ROOT_SITE ?>/admin/system/">System Maintenance</a>
                        </li>
                        <li>
                            <a href="/..<?php echo ROOT_SITE ?>/admin/list/">User List</a>
                        </li>
                        <li>
                            <a href="/..<?php echo ROOT_SITE ?>/admin/log/">Log</a>
                        </li>
                    </ul>
                </li>
            <?php endif ?>
            <li>
                <a href="/..<?php echo ROOT_SITE ?>/course/">Course</a>
                <ul>
                    <li>
                        <a href="/..<?php echo ROOT_SITE ?>/course/view/">View</a>
                    </li>
                </ul>
            </li>
            <li>
                <a href="/..<?php echo ROOT_SITE ?>/schedule/">Schedule</a>
                <ul>
                    <li>
                        <a href="/..<?php echo ROOT_SITE ?>/schedule/view/">View</a>
                    </li>
                    <?php if ($user_role === 'tutor') : ?>
                        <li>
                            <a href="/..<?php echo ROOT_SITE ?>/schedule/book/">Book</a>
                        </li>
                    <?php endif ?>
                    <?php if ($user_role === 'eru') : ?>
                        <li>
                            <a href="/..<?php echo ROOT_SITE ?>/schedule/add/">Add</a>
                        </li>
                        <li>
                            <a href="/..<?php echo ROOT_SITE ?>/schedule/edit/">Edit</a>
                        </li>
                    <?php endif ?>
                </ul>
            </li>
            <li>
                <a href="/..<?php echo ROOT_SITE ?>/grade/">Grade</a>
                <ul>
                    <li>
                        <a href="/..<?php echo ROOT_SITE ?>/grade/view/">View</a>
                    </li>
                    <?php if ($user_role === 'eru') : ?>
                        <li>
                            <a href="/..<?php echo ROOT_SITE ?>/grade/publish/">Publish</a>
                        </li>
                    <?php endif ?>
                </ul>
            </li>
            <?php if ("/" != str_replace([str_replace('\\', '/', ROOT_PATH), "index.php"], '', $_SERVER["SCRIPT_FILENAME"])) : ?>
                <li><a href="<?php echo ROOT_SITE ?>">Back</a></li>
            <?php endif ?>
            <li>
                <a href=<?php echo ROOT_SITE . '/profile/' ?>>Profile</a>
            </li>
            <li><a href="<?php echo ROOT_SITE ?>/logout/">Log Out</a></li>
        <?php else : ?>
            <li><a href="<?php echo ROOT_SITE ?>/register/">Register</a></li>
            <li><a href="<?php echo ROOT_SITE ?>/login/">Log In</a></li>
        <?php endif ?>
    </ul>
</nav>