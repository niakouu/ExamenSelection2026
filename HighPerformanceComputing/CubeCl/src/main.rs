use cubecl::prelude::*;

// This function will be executed in parallel on the GPU/CPU
// Lookup the variable ABSOLUTE_POS to get started!
#[cube(launch_unchecked)]
fn compute_bbf<F: Float>(max_iter: u32, vec_size: u32, output: &mut Array<f32>) {}

fn final_sum() -> f64 {
    0.0
}

pub fn launch<R: Runtime>(device: &R::Device) {
    let vectorization = 4usize;
    let max_iter = 1000_00_000u32;

    let result = 0;

    println!("Answer => {result}",);
}

fn launch_cubcl() {
    #[cfg(feature = "cuda")]
    {
        print!("Launching with CUDA runtime...\n");
        launch::<cubecl::cuda::CudaRuntime>(&Default::default());
    }

    #[cfg(feature = "wgpu")]
    {
        print!("Launching with WGPU runtime...\n");
        launch::<cubecl::wgpu::WgpuRuntime>(&Default::default());
    }

    #[cfg(feature = "cpu")]
    {
        print!("Launching with CPU runtime...\n");
        launch::<cubecl::cpu::CpuRuntime>(&Default::default());
    }
}

fn main() {
    println!("Bailey-Borwein-Plouffe with cubecl!");
    launch_cubcl();
}
