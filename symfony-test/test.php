<?php
require_once __DIR__ . '/vendor/autoload.php';

use App\Kernel;
use Symfony\Component\HttpFoundation\Request;

$kernel = new Kernel('dev', true);
$request = Request::create('http://localhost/blog/3/edit');
$response = $kernel->handle($request);
$kernel->terminate($request, $response);

