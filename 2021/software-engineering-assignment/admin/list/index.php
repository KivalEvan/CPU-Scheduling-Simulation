<?php
require_once(__DIR__ . "/../../includes/constants.php");
include(__DIR__ . "/../../includes/session.php");

$query = "SELECT user_name, user_fname, user_lname, user_email FROM user";
$qry_result = "No user in database";
$search_name = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    if (isset($_POST["search_name"]) && !(empty(trim($_POST["search_name"])))) {
        $search_name = trim($_POST["search_name"]);
        $query = "SELECT user_name, user_fname, user_lname, user_email FROM user WHERE user_fname LIKE '%$search_name%' OR user_lname LIKE '%$search_name%'";
    }
    if (isset($_POST["order_by"]) && isset($_POST["order_in"]) && !(empty(trim($_POST["order_by"]))) && !(empty(trim($_POST["order_in"])))) {
        $order_by = trim($_POST["order_by"]);
        $order_in = trim($_POST["order_in"]);
        $query = "SELECT user_name, user_fname, user_lname, user_email FROM user ORDER BY $order_by $order_in";
    }
}

$result = mysqli_query($db, $query) or die(mysqli_error($db));
$user_array = [];
while ($row = mysqli_fetch_array($result)) {
    $user_array[] = array($row['user_name'], $row['user_fname'] . ' ' . $row['user_lname'], $row['user_email']);
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
                    View User List
                </div>
                <br>
                <form action="" method="post">
                    <label for="order_by">Order by: </label>
                    <select id="order_by" name="order_by">
                        <option value="user_fname">Name</option>
                        <option value="user_email">Email</option>
                        <option value="user_name">ID</option>
                    </select>
                    <label for="order_in">in: </label>
                    <select id="order_in" name="order_in">
                        <option value="ASC">Ascending</option>
                        <option value="DESC">Descending</option>
                    </select>
                    <input type="submit" value="Sort">
                </form>
                <form action="" method="post">
                    <label for="search_name">Search Name: </label>
                    <input type="text" id="search_name" name="search_name" value=<?php echo $search_name ?>>
                    <input type="submit" value="Search">
                </form>
                <br>
                <table>
                    <thead>
                        <tr>
                            <th class="table-join">User ID</th>
                            <th class="table-join">Name</th>
                            <th class="table-join">Email</th>
                        </tr>
                    </thead>
                    <?php if (count($user_array)) : ?>
                        <?php foreach ($user_array as $user) : ?>
                            <tr class="table-join">
                                <td class="table-join"><?php echo $user[0] ?></td>
                                <td class="table-join"><?php echo $user[1] ?></td>
                                <td class="table-join"><?php echo $user[2] ?></td>
                            </tr>
                        <?php endforeach ?>
                    <?php else : ?>
                        <tr class="table-join">
                            <td colspan=3><?php echo $qry_result ?></td>
                        </tr>
                    <?php endif ?>
                </table>
            </div>
        </div>
    </main>
    <?php include_once(ROOT_PATH . '/includes/footer.php') ?>
</body>

</html>