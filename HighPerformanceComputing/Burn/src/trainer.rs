pub struct Trainer {
    pub inputs: [f32; 3],
    pub answer: i32,
}

impl Trainer {
    pub fn new(x: f32, y: f32, answer: i32) -> Self {
        Self {
            inputs: [x, y, 1.0],
            answer,
        }
    }
}
