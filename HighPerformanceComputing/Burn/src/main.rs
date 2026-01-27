mod perceptron;
mod trainer;

use perceptron::Perceptron;
use raylib::prelude::*;
use trainer::Trainer;

const WIDTH: i32 = 600;
const HEIGHT: i32 = 600;
const NB_VALUES: usize = 2000;

// The function to approcimate using a perceptron: y = 2x + 20
fn f(x: f32) -> f32 {
    2.0 * x + 20.0
}

fn draw(d: &mut RaylibDrawHandle, perceptron: &Perceptron, trainers: &[Trainer], count: usize) {
    d.clear_background(Color::WHITE);

    let half_width = WIDTH as f32 / 2.0;

    let center_x = WIDTH / 2;
    let center_y = HEIGHT / 2;

    let x1 = -half_width;
    let y1 = f(x1);
    let x2 = half_width;
    let y2 = f(x2);

    let screen_x1 = center_x + x1 as i32;
    let screen_y1 = center_y - y1 as i32;
    let screen_x2 = center_x + x2 as i32;
    let screen_y2 = center_y - y2 as i32;

    d.draw_line(screen_x1, screen_y1, screen_x2, screen_y2, Color::BLACK);

    for trainer in trainers {
        let outline_color = if trainer.answer < 0 {
            Color::GREEN
        } else {
            Color::RED
        };

        let guess = perceptron.feed_forward(&trainer.inputs);

        let screen_x = center_x + trainer.inputs[0] as i32;
        let screen_y = center_y - trainer.inputs[1] as i32;

        if guess > 0 {
            d.draw_circle_lines(screen_x, screen_y, 4.0, outline_color);
        } else {
            d.draw_circle(screen_x, screen_y, 4.0, outline_color);
        }
    }

    let weights = perceptron.get_weights();
    let info = format!(
        "Training sample: {}\nWeights: [{:.4}, {:.4}, {:.4}]",
        count, weights[0], weights[1], weights[2]
    );
    d.draw_text(&info, 10, 10, 16, Color::BLACK);
}

fn main() {
    let (mut rl, thread) = raylib::init()
        .size(WIDTH, HEIGHT)
        .title("Perceptron - Rust + Burn + Raylib")
        .build();

    rl.set_target_fps(60);

    let mut perceptron = Perceptron::new(3);

    let mut trainers: Vec<Trainer> = Vec::with_capacity(NB_VALUES);
    let half_width = WIDTH as f32 / 2.0;
    let half_height = HEIGHT as f32 / 2.0;

    for _ in 0..NB_VALUES {
        let x = rand::random::<f32>() * WIDTH as f32 - half_width;
        let y = rand::random::<f32>() * HEIGHT as f32 - half_height;
        let answer = if y < f(x) { -1 } else { 1 };
        trainers.push(Trainer::new(x, y, answer));
    }

    let mut count: usize = 0;

    while !rl.window_should_close() {
        perceptron.train(&trainers[count].inputs, trainers[count].answer);
        count = (count + 1) % trainers.len();

        draw(
            &mut rl.begin_drawing(&thread),
            &perceptron,
            &trainers,
            count,
        );
    }
}
