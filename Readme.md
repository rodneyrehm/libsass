# Libsass - Emscripten Fork

This is a fork of the official [libsass](https://github.com/hcatlin/libsass/) repository. Functionality of libsass has not been altered. This fork only contains modifications pertinent to compiling `libsass.js` using [Emscripten](https://github.com/kripken/emscripten/). 

> A fair warning: minified it's 2MB, gzipped it's 550KB.

See the [live example](http://rodneyrehm.github.io/libsass/) 

---

## Using `libsass.js`

I created two wrappers [`sass.js`](https://github.com/rodneyrehm/libsass/blob/emscripten/js/sass.js) and [`sass.worker.js`](https://github.com/rodneyrehm/libsass/blob/emscripten/js/sass.worker.js) so we don't have to know anything about Emscripten in order to compile stuff.

```javascript
var scss = "$foo: 123px; .selector { width: $foo; }";
var css = Sass.compile(scss, Sass.style.);
console.log(css);
```

outputs

```css
.selector {
  width: 123px; }
```

### Working With Files

Chances are you want to use one of the readily available Sass mixins (e.g. [drublic/sass-mixins](https://github.com/drublic/Sass-Mixins) or [Burbon](https://github.com/thoughtbot/bourbon)). While I haven't created a fully featured "loadBurbon()", registering files is possible:

```javascript
Sass.writeFile('one.scss', '.one { width: 123px; }');
Sass.writeFile('some-dir/two.scss', '.two { width: 123px; }');
Sass.compile('@import "one"; @import "some-dir/two";');
```

outputs

```css
.one {
  width: 123px; }

.two {
  width: 123px; }
```

## Known Problems

* compile styles `nested`, `expanded` and `compact` seem to behave exactly the same
* compile style `compressed` prefixes every selector with `&`

(I haven't looked into why this is happending)

---

## Compiling `libsass.js` Yourself

### Environment

1. Make sure you've got `python2`! If `which python2` says "python2 not found" run `sudo ln -s /usr/bin/python /usr/bin/python2` which will simply make the current python installation available under the name python2. Maybe check that it really is Python version 2 using `python --version`. If it's not, download and install Python 2.
2. Download [Emscripten Portable SDK](https://github.com/kripken/emscripten/wiki/Emscripten-SDK#downloads).
3. Install the Portable SDK and run `source emsdk_add_path` (or add that to your `PATH` if you plan on using emscripten beyond a test-run).

### Compiling `libsass`

This repository contains a modified `Makefile` and adds `emscripten_wrapper.cpp`. Make sure they are present.

1. run `emmake make` to build / link / whatever.
2. run `emcc -O2 libsass.a -o js/libsass.js -s EXPORTED_FUNCTIONS="['_sass_compile_unrolled']" -s DISABLE_EXCEPTION_CATCHING=0 && du -sh libsass.js` to compile the build to JavaScript. The file will be available at `src/libsass.js`.

`EXPORTED_FUNCTIONS` lists the names of the C++ functions we want to be accessible in JavaScript. The `DISABLE_EXCEPTION_CATCHING` is necessary because libsass uses exceptions internally. If you omit this you get a much smaller file (about 1.9MB instead of 2.4MB) - but you will *not* get any feedback on parser errors. `Sass.compile()` in JavaScript will simply return `{line: null, message: "Unknown Error" }`

### Minifying `libsass.js`

1. download [Google Closure Compiler](https://developers.google.com/closure/compiler/) ([compiler-latest.zip](http://dl.google.com/closure-compiler/compiler-latest.zip))
2. run `java -jar compiler-latest/compiler.jar --compilation_level SIMPLE_OPTIMIZATIONS --language_in ECMASCRIPT5 --warning_level QUIET --js js/libsass.js --js_output_file js/libsass.min.js`. Note that `ADVANCED_OPTIMIZATION` will break the JavaScript.


---

## What You Didn't Want To Know

I have no idea what I'm doing. My C++ is as good as your Klingon. My understanding of Emscripten is on par with your understanding of rocket science. I still got it to work, though. [Christian Kruse](https://github.com/ckruse) and [Andres Freund](https://github.com/anarazel) will happily tell you all about how [Tobias Tom](https://github.com/tobiastom) annihilated tons of popcorn watching the three of us suffer because of my utter incompetence. I wouldn't have looked into this if it wasn't for [Sebastian Golasch](http://github.com/asciidisco). And none of us would've gotten anywhere with Emscripten if it wasn't for [Alon Zakai](http://github.com/kripken).

## License

Do what the f* you like. If that doesn't work for you, the MIT License should!