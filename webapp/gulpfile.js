var gulp = require('gulp');
var rename = require('gulp-rename');
var sass = require('gulp-sass');
var plumber = require('gulp-plumber');
var autoprefixer = require('gulp-autoprefixer');
var sourcemaps = require('gulp-sourcemaps');
var concat = require('gulp-concat');
var notify = require("gulp-notify");
var compass = require("gulp-compass");

gulp.task('sass', function() {

	gulp.src('assets/css/scss/*.scss')
	//.pipe(plumber())
	.pipe(sourcemaps.init())
	.pipe(sass({outputStyle: 'compact'}).on("error", notify.onError({
		message: "Error: <%= error.message %>",
		title: "Gulp compilation failed."
	})))
	.pipe(autoprefixer({
		browsers: ['last 2 versions']
	}))
	.pipe(sourcemaps.write('./'))
	.pipe(gulp.dest('./assets/css/'))
	//.pipe(exit());
});

gulp.task('watch', function () {
	gulp.watch('assets/css/scss/*.scss', [ "sass" ]);
});

gulp.task('default', ["sass"]);
