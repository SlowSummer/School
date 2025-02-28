// EDIT THIS FILE TO COMPLETE ASSIGNMENT QUESTION 1
const { chromium } = require("playwright");

async function sortHackerNewsArticles() {
  // launch browser
  const browser = await chromium.launch({ headless: false });
  const context = await browser.newContext();
  const page = await context.newPage();

  // go to Hacker News
  await page.goto("https://news.ycombinator.com/newest");

  let articles = [];

  while (articles.length < 100) {
    // Wait for articles to load
    await page.waitForSelector(".athing");

    // Extract articles
    let newArticles = await page.$$eval(".athing", (rows) =>
      rows.map((row) => ({
        id: row.getAttribute("id"),
      }))
    );

    // Avoid duplicates (some articles may reload)
    newArticles = newArticles.filter(
      (article) => !articles.some((a) => a.id === article.id)
    );

    articles.push(...newArticles);

    console.log(`Loaded ${articles.length} articles...`);

    // If we still need more, click "More"
    if (articles.length < 100) {
      const moreButton = await page.$("a.morelink");
      if (moreButton) {
        await moreButton.click();
        await page.waitForTimeout(2000); // Wait for the page to load
      } else {
        console.error("No 'More' button found. Stopping.");
        break;
      }
    }
  }

  if (articles.length < 100) {
    console.error(`Expected 100 articles, but only found ${articles.length}.`);
    await browser.close();
    process.exit(1);
  }

  // Extract timestamps for first 100 articles
  let timestamps = [];
  for (let i = 0; i < 100; i++) {
    const id = articles[i].id;
    const timeSelector = `#score_${id} + span`;
    const timeText = await page.textContent(timeSelector);

    // Convert relative time (e.g., "10 minutes ago") into seconds
    const match = timeText.match(/(\d+)\s*(second|minute|hour|day)s?\s*ago/);
    if (match) {
      let value = parseInt(match[1]);
      let unit = match[2];

      let timestamp = 0;
      if (unit === "second") timestamp = value;
      else if (unit === "minute") timestamp = value * 60;
      else if (unit === "hour") timestamp = value * 3600;
      else if (unit === "day") timestamp = value * 86400;

      timestamps.push(timestamp);
    } else {
      console.warn(`Could not extract time from article ${id}: ${timeText}`);
    }
  }

  // Validate sorting (newest to oldest means timestamps should be decreasing)
  for (let i = 0; i < timestamps.length - 1; i++) {
    if (timestamps[i] < timestamps[i + 1]) {
      console.error(`Articles are not sorted correctly. Error at index ${i}`);
      await browser.close();
      process.exit(1);
    }
  }

  console.log(" Articles are correctly sorted from newest to oldest.");

  await browser.close();
}

(async () => {
  await sortHackerNewsArticles();
})();
