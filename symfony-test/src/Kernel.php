<?php

namespace App;

use App\Controller\BlogController;
use App\Controller\SubRequestController;
use Symfony\Bundle\FrameworkBundle\FrameworkBundle;
use Symfony\Bundle\FrameworkBundle\Kernel\MicroKernelTrait;
use Symfony\Bundle\MonologBundle\MonologBundle;
use Symfony\Bundle\TwigBundle\TwigBundle;
use Symfony\Component\Config\Loader\LoaderInterface;
use Symfony\Component\DependencyInjection\ContainerBuilder;
use Symfony\Component\HttpFoundation\Response;
use Symfony\Component\HttpKernel\Kernel as BaseKernel;
use Symfony\Component\Routing\RouteCollectionBuilder;

class Kernel extends BaseKernel
{
    use MicroKernelTrait;

    public function registerBundles()
    {
        return [
            new FrameworkBundle(),
            new MonologBundle(),
            new TwigBundle(),
        ];
    }

    protected function configureContainer(ContainerBuilder $c, LoaderInterface $loader)
    {
        $c->loadFromExtension('framework', [
            'secret' => 'S0ME_SECRET'
        ]);

        $c->setParameter('foo', 'bar');

        $c->register(BlogController::class)
            ->setAutoconfigured(true)
            ->setAutowired(true);

        $c->register(SubRequestController::class)
            ->setAutoconfigured(true)
            ->setAutowired(true);
    }

    protected function configureRoutes(RouteCollectionBuilder $routes)
    {
        $routes->add('/random/{limit}', 'kernel::randomNumber', 'random_number');
        $routes->add('/blog/{id}/edit', 'App\\Controller\\BlogController::edit', 'blog_edit');
        $routes->add('/sub-request/{arbitrary}/{blog_id}', 'App\\Controller\\SubRequestController::handle', 'sub_request_handler');
    }

    public function randomNumber($limit)
    {
        return new Response();
    }

    public function getCacheDir()
    {
        return __DIR__.'/../var/cache/'.$this->getEnvironment();
    }

    public function getLogDir()
    {
        return __DIR__.'/../var/log';
    }
}
