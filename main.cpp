    // #include "color.h"
// #include "ray.h"
// #include "vec3.h"
// #include <iostream>

#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
// double hit_sphere(const point3& center, double radius, const ray&r){
//     vec3 oc = center - r.origin();
//     auto a = r.direction().length_squared();
//     auto h =  dot(r.direction(), oc);
//     auto c = dot(oc,oc) - radius*radius;
//     auto discriminant = h*h - a*c;
//     // return (discriminant >=0);

//     if (discriminant < 0){
//         return -1.0;
//     } else {
//         return(h - std::sqrt(discriminant))/a ;
//     }
// }

// color ray_color(const ray& r , const hittable& world){
//     hit_record rec;
//     if (world.hit(r,interval(0,infinity),rec)) {
//         return 0.5*(rec.normal + color(1,1,1));
//     }

//     // auto t = hit_sphere(point3(0,0,-1),0.5,r);
//     // if (t>0.0) {
//     //     vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
//     //     return 0.5*color(N.x()+1, N.y()+1,N.z()+1);
//     // }

//     // if (hit_sphere(point3(0,0,-1),0.7,r))
//     //     return color(0.3,0.5,0.7);
//     vec3 unit_direction = unit_vector(r.direction());
//     auto a = 0.5*(unit_direction.y() + 1.0);
//     return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
// }

int main(){
    //image
    // 
    // lets calculate using aspect ratio 16:9

    // auto aspect_ratio = 16.0/9.0;
    // int image_width = 400;

    // int image_height = int(image_width/aspect_ratio);
    // image_height = (image_height < 1) ? 1: image_height;

    hittable_list world;

    auto R = std::cos(pi/4);

    auto material_ground = make_shared<lambertian>(color(0.5,0.5,0.5));
    world.add(make_shared<sphere>(point3(0.0,-1000,0.0),1000.0,material_ground));

    for (int a = -11; a < 11; a++){
        for (int b =-11; b<11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(),0.2, b+0.9*random_double());

            if ((center - point3(4,0.2,0)).length()>0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat<0.8){
                    //diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center,0.2,sphere_material));

                } else if (choose_mat<0.95){
                    //metal
                    auto albedo = color::random(0.5,1);
                    auto fuzz = random_double(0,0.5);
                    sphere_material = make_shared<metal>(albedo,fuzz);
                    world.add(make_shared<sphere>(center,0.2,sphere_material));

                } else {
                    //glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center,0.2,sphere_material));
                }
            }
        }
    }
    auto material_center = make_shared<lambertian>(color(0.4,0.2,0.1));
    auto material_left = make_shared<dielectric>(1.50);
    auto material_bubble = make_shared<dielectric>(1.00/1.50);
    auto material_right = make_shared<metal>(color(0.7,0.6,0.5), 0.0);
    


    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material_center));
    world.add(make_shared<sphere>(point3(0.0,1.0,0.0), 1.0, material_left));
    world.add(make_shared<sphere>(point3(0.0, 1.0, 0.0), 0.9, material_bubble));
    world.add(make_shared<sphere>(point3(4.0 , 1.0, 0.0), 1.0, material_right));

    camera cam;

    cam.aspect_ratio = 16.0 /9.0;
    cam.image_width = 400;
    cam.samples_per_pixel=1000;
    cam.max_depth = 50;
    cam.vfov = 30;
    cam.lookfrom = point3(13,2,3);
    cam.lookat = point3(0,0,0);
    cam.vup = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10;

    cam.render(world);


    //camera

    // auto focal_length = 1.0;
    // auto viewport_height = 2.0;
    // auto viewport_width = viewport_height * (double(image_width)/image_height);
    // auto camera_center = point3(0,0,0);

    // auto viewport_u = vec3(viewport_width,0,0);
    // auto viewport_v = vec3(0,-viewport_height,0);

    // auto pixel_delta_u = viewport_u / image_width;
    // auto pixel_delta_v = viewport_v / image_height;

    // auto viewport_upper_left = camera_center - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
    // auto pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);



    //Render
    // std::cout<<"P3\n"<<image_width<<' '<<image_height<<"\n255\n";
    // for(int j =0;j<image_height;j++){
    //     std::clog<<"\rscanlines remaining" << (image_height - j)<<' '<<std::flush;
    //     for(int i=0;i<image_width;i++){

    //         auto pixel_center = pixel100_loc + (i* pixel_delta_u) + (j*pixel_delta_v);
    //         auto ray_direction = pixel_center - camera_center;
    //         ray r(camera_center, ray_direction);

    //         color pixel_color = ray_color(r, world);
    //         write_color(std::cout, pixel_color);

            // auto r = double(i)/(image_width-1);
            // auto g = double(j)/(image_height-1);
            // auto b = 0.0;

            // int ir = int(255.99*r);
            // int ig = int(255.99*g);
            // int ib = int(255.99*b);

            // std::cout<<ir<<' '<<ig<<' '<<ib<<"\n";



    //     }
    // }

}