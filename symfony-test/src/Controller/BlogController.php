<?php

namespace App\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\HttpFoundation\Response;

class BlogController extends AbstractController
{
    public function edit(Request $request)
    {
        $this->renderView('blog/edit.html.twig');
        // return empty content so it's safely ignored in test
        return new Response();
    }
}
