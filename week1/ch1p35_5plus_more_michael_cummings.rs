#![allow(non_snake_case)]
/*
 * Michael Cummings
 * CS-131 08:30am
 * Ch1p35_5PlusMore
 * Data: 20180404
 */
use std::io;
/*
 * Takes width and height of area in feet and calculates amount of fencing needed.
 */
fn main() {
    // Prompt user
    println!("Press 'return' after entering numbers.");
    let height: f32;
    let width: f32;
    let mut input = String::new();
    loop {
        println!("Enter the width of area in feet:");
        // Input width as string.
        match io::stdin().read_line(&mut input) {
            // Ignore integer char count from read_line() here as the string is in width.
            Ok(_) => {
                match input.trim().parse() {
                    Ok(num) => {
                        width = num;
                        break;
                    }
                    Err(error) => {
                        println!("error: {}", error);
                        continue;
                    }
                };
            }
            Err(error) => {
                println!("error: {}", error);
                continue;
            }
        };
    }
    input = String::new();
    loop {
        println!("Enter the height of area in feet:");
        // Input width as string.
        match io::stdin().read_line(&mut input) {
            // Ignore integer char count from read_line() here as the string is in height.
            Ok(_) => {
                match input.trim().parse() {
                    Ok(num) => {
                        height = num;
                        break;
                    }
                    Err(error) => {
                        println!("error: {}", error);
                        continue;
                    }
                };
            }
            Err(error) => {
                println!("error: {}", error);
                continue;
            }
        };
    }
    // Calculate
    let total_length = width * 2.0 + height * 2.0;
    // Output
    println!("If you have an area with width of {:.3} feet", width);
    println!("and a height of {:.3} feet, then", height);
    println!("you need a total of {:.3} feet of fencing to enclose it.", total_length);
    input = String::new();
    // Wait to continue.
    loop {
        println!("Enter 'x' to exit or 'c' to continue then 'return':");
        match io::stdin().read_line(&mut input) {
            Ok(_) => {
                if input.contains("c") {
                    break;
                } else if input.contains("x") {
                    std::process::exit(0);
                }
                continue;
            }
            Err(error) => {
                println!("error: {}", error);
                continue;
            }
        };
    }
    // Plus more.
    println!("Plus more stuff just for Robin!!!\n");
    println!("The sum of the width and height is {}", (width + height));
    println!("The diff of the width and height is {}", (width - height));
    println!("The area of the width and height is {}", (width * height));
    println!("The ratio of the width and height is {}", (width / height));
    println!("Done.");
    loop {
        println!("Enter 'x' to exit or 'c' to continue then 'return':");
        match io::stdin().read_line(&mut input) {
            Ok(_) => {
                if input.contains("c") {
                    break;
                } else if input.contains("x") {
                    std::process::exit(0);
                }
                continue;
            }
            Err(error) => {
                println!("error: {}", error);
                continue;
            }
        };
    }
}
