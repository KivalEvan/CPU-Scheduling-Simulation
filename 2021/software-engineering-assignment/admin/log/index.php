<?php
require_once(__DIR__ . "/../../includes/constants.php");
include(__DIR__ . "/../../includes/session.php");

$query = "SELECT * FROM log";
$result = mysqli_query($db, $query) or die(mysqli_error($db));
$logs = [];
while ($row = mysqli_fetch_array($result)) {
    $logs[] = array($row['log_timestamp'], $row['log_type'], $row['log_content']);
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
        <?php include_once(ROOT_PATH . '/includes/navigation.php') ?>
        <div class="content">
            <div class="content-wrapper">
                <div class="content-header">
                    View Log
                </div>
                <br>
                <table>
                    <thead>
                        <tr>
                            <th class="table-join">Timestamp</th>
                            <th class="table-join">Type</th>
                            <th class="table-join">Text</th>
                        </tr>
                    </thead>
                    <?php if (count($logs)) : ?>
                        <?php foreach ($logs as $log) : ?>
                            <tr class="table-join">
                                <td class="table-join"><?php echo $log[0] ?></td>
                                <td class="table-join"><?php echo $log[1] ?></td>
                                <td class="table-join"><?php echo $log[2] ?></td>
                            </tr>
                        <?php endforeach ?>
                    <?php else : ?>
                        <tr class="table-join">
                            <td colspan=3>No log</td>
                        </tr>
                    <?php endif ?>
                </table>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>