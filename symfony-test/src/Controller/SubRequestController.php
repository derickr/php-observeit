<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Response;

class SubRequestController extends AbstractController
{
    public function handle($arbitrary, $blog_id)
    {
        $response = $this->forward('App\Controller\BlogController::edit', [
            'id'  => $blog_id,
            'color' => 'green',
            'arbitrary' => $arbitrary,
        ]);

        return new Response();
    }
}
